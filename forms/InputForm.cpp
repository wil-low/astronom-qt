#include "InputForm.h"
#include "ui_InputForm.h"
#include "../utils/Ephemeris.h"
#include "../utils/DMS.h"
#include "../utils/convertors/NatalConvertor.h"

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
		import(mimeData->text());
	}
	else {
		QMessageBox::warning(this, "Unknown data", "");
	}
}

void InputForm::import(const QString& str)
{
	NatalConvertor convertor(str, BaseConvertor::MODE_ASTROZET);
	if (convertor.isValid()) {
		QString str;
		if (convertor.getString(BaseConvertor::STR_NAME, str))
			ui->editName->setText(str);
		QDate date;
		if (convertor.getDate(BaseConvertor::DT_NATAL_DATE, date))
			ui->editDate->setDate(date);
		QTime time;
		if (convertor.getTime(BaseConvertor::DT_NATAL_TIME, time))
			ui->editTime->setTime(time);
		if (convertor.getTime(BaseConvertor::DT_UTC_OFFSET, time))
			ui->editUTCOffset->setTime(time);
		//if (convertor.getString(BaseConvertor::STR_LOCATION_NAME, str))
		//ui->cboLocationName->setItemText(str);
		if (convertor.getString(BaseConvertor::STR_LONGITUDE, str))
			ui->editLon->setText(str);
		if (convertor.getString(BaseConvertor::STR_LATITUDE, str))
			ui->editLat->setText(str);
	}
}
