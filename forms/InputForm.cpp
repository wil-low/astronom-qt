#include "InputForm.h"
#include "ui_InputForm.h"
#include "../utils/Ephemeris.h"
#include "../utils/DMS.h"
#include "../utils/convertors/NatalConvertor.h"

#include <QClipboard>
#include <QMimeData>
#include <QMessageBox>

InputForm::InputForm(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::InputForm)
{
    ui->setupUi(this);
	ui->editLat->setInputMask("000°00'00\"A;_");
	ui->editLon->setInputMask("000°00'00\"A;_");

	tl_.name_ = "Sample Name";
	tl_.location_ = "Sample location";
	tl_.data_[TL_LAT] = 45;
	tl_.data_[TL_LON] = 34;

	fromTimeLoc(tl_);
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
	ui->editName->setText(tl_.name_);
	//ui->cboLocationName->setText(tl_.location_);

	setDateTime(tl_.data_[TL_DATETIME]);

	DMS dmsLat(tl_.data_[TL_LAT], DMS::COORD_LAT);
	ui->editLat->setText(dmsLat.toMaskedString());
	DMS dmsLon(tl_.data_[TL_LON], DMS::COORD_LON);
	ui->editLon->setText(dmsLon.toMaskedString());
}

const TimeLoc& InputForm::toTimeLoc ()
{
	QDate date = ui->editDate->date();
	QTime time = ui->editTime->time();
	tl_.data_[TL_DATETIME] = Ephemeris::julday (date.year(), date.month(), date.day(),
												time.hour(), time.minute(), time.second());
	DMS dmsLat(ui->editLat->text(), DMS::COORD_LAT);
	tl_.data_[TL_LAT] = dmsLat.angle();

	DMS dmsLon(ui->editLon->text(), DMS::COORD_LON);
	tl_.data_[TL_LON] = dmsLon.angle();
	tl_.name_ = ui->editName->text();
	tl_.location_ = ui->cboLocationName->currentText();

	titleStr_ = ui->editName->text() + ", " + ui->cboLocationName->currentText() + ", " +
				date.toString(Qt::SystemLocaleShortDate) + " " +
				time.toString(Qt::SystemLocaleShortDate) + ", " +
				ui->editLat->text() + " " + ui->editLon->text();
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

const QString& InputForm::titleStr() const
{
	return titleStr_;
}
