#include "InputForm.h"
#include "ui_InputForm.h"
#include "../utils/Ephemeris.h"
#include "../utils/DMS.h"

#include <QClipboard>
#include <QMimeData>
#include <QMessageBox>
#include <QTextCodec>
#include <QRegExp>

InputForm::InputForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputForm)
{
    ui->setupUi(this);
	ui->editLat->setInputMask("000°00'00'';_");
	ui->editLon->setInputMask("#00°00'00'';_");
	ui->editLon->setText("0340000");
	ui->editLat->setText("0450000");

	on_btnNow_clicked();
}

InputForm::~InputForm()
{
    delete ui;
}

void InputForm::on_btnOK_clicked()
{
	toTimeLoc();
	accept();
}

void InputForm::on_btnCancel_clicked()
{
	reject();
}

void InputForm::on_btnNow_clicked()
{
	setDateTime(Ephemeris::now());
}

void InputForm::fromTimeLoc (const TimeLoc& tl)
{
	tl_ = tl;
	setDateTime(tl_.data_[TL_DATETIME]);

	DMS dms(tl_.data_[TL_LON]);
	ui->editLon->setText(dms.toMaskedString());
	dms.calculate(tl_.data_[TL_LAT]);
	ui->editLat->setText(dms.toMaskedString());

}

const TimeLoc& InputForm::toTimeLoc ()
{
	QDate date = ui->editDate->date();
	QTime time = ui->editTime->time();
	tl_.data_[TL_DATETIME] = Ephemeris::julday (date.year(), date.month(), date.day(),
												time.hour(), time.minute(), time.second());
	DMS dms(ui->editLat->text());
	tl_.data_[TL_LAT] = dms.angle();

	dms.calculate(ui->editLon->text());
	tl_.data_[TL_LON] = dms.angle();
	return tl_;
}

void InputForm::setDateTime(double jday)
{
	int y, m, d, h, min, s;
	Ephemeris::revjul (jday, &y, &m, &d, &h, &min, &s);
	ui->editDate->setDate(QDate(y, m, d));
	ui->editTime->setTime(QTime(h, min, s));
}

void InputForm::on_btnCopy_clicked()
{

}

void InputForm::on_btnPaste_clicked()
{
	const QClipboard *clipboard = QApplication::clipboard();
	const QMimeData *mimeData = clipboard->mimeData();

	if (mimeData->hasImage()) {
		QMessageBox::warning(this, "Has image", "");
	}
	else if (mimeData->hasHtml()) {
		QMessageBox::warning(this, "Has html", mimeData->text());
	}
	else if (mimeData->hasText()) {
		import(mimeData->text(), IMPORT_ASTROZET);
	}
	else {
		QMessageBox::warning(this, "Unknown data", "");
	}
}

bool InputForm::import(const QString& str, InputForm::import_mode_t mode)
{
	switch (mode) {
	case IMPORT_ASTROZET:
		QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
		QString decodedStr = codec->toUnicode(str.toAscii());
		//QMessageBox::warning(this, "Has text", decodedStr);
		QStringList sections = decodedStr.split(';');
		ui->editName->setText(sections[0]);
		QRegExp rx("(\\d+)\.(\\d+)\.(\\d+)");
		if (rx.indexIn(sections[1]) != -1) {
			ui->editDate->setDate(QDate(rx.cap(3).toInt(), rx.cap(2).toInt(), rx.cap(1).toInt()));
		}
		rx.setPattern("(\\d+):(\\d+):(\\d+)");
		if (rx.indexIn(sections[2]) != -1) {
			ui->editTime->setTime(QTime(rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt()));
		}
		rx.setPattern("([\+\-]\\d+):(\\d+):(\\d+)");
		if (rx.indexIn(sections[3]) != -1) {
			ui->editUTCOffset->setTime(QTime(rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt()));
		}
		//ui->cboLocationName->setItemText(sections[4]);
		ui->editLon->setText(sections[5]);
		ui->editLat->setText(sections[6]);
	}

	return true;
}
