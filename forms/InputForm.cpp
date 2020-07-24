#include "InputForm.h"
#include "ui_InputForm.h"
#include "../utils/Ephemeris.h"
#include "../utils/DMS.h"
#include "../utils/convertors/NatalConvertor.h"

#include <QClipboard>
#include <QMimeData>
#include <QMessageBox>
#include <QDebug>
#include <stdio.h>

InputForm::InputForm(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::InputForm)
{
    ui->setupUi(this);

	ui->editLat->setCoordType(DMS::COORD_LAT);
	ui->editLon->setCoordType(DMS::COORD_LON);

	tl_.name_ = "Sample Name";
	tl_.location_ = "Sample location";
	tl_.str_[TL_LAT] = "+0450000";
	tl_.str_[TL_LON] = "+0340000";
	tl_.str_[TL_TZ]  = "-032657";

	on_btnNow_clicked();
	fromTimeLoc(tl_);
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
	tl_.str_[TL_DATETIME] = QDateTime::currentDateTime().toString(Qt::ISODate);
	setDateTime();
}

void InputForm::fromTimeLoc (const TimeLoc& tl)
{
	tl_ = tl;
	ui->editName->setText(tl_.name_);
	//ui->cboLocationName->setText(tl_.location_);

	setDateTime();

	DMS dms;
	dms.fromCoord(tl_.str_[TL_LAT], DMS::COORD_LAT);
	ui->editLat->setText(dms.toMaskedString());
	dms.fromCoord(tl_.str_[TL_LON], DMS::COORD_LON);
	ui->editLon->setText(dms.toMaskedString());
	dms.fromOffset(tl_.str_[TL_TZ]);
	ui->editUTCOffset->setText(dms.toMaskedString());
}

const TimeLoc& InputForm::toTimeLoc ()
{
	tl_.name_ = ui->editName->text();
	tl_.location_ = ui->cboLocationName->currentText();
	QDate date = ui->editDate->date();
	QTime time = ui->editTime->time();
	tl_.str_[TL_DATETIME] = QDateTime(date, time).toString(Qt::ISODate);
	tl_.str_[TL_LAT] = ui->editLat->dbText();
	tl_.str_[TL_LON] = ui->editLon->dbText();
	tl_.str_[TL_TZ] = ui->editUTCOffset->dbText();

	tl_.recalculate(true);
	titleStr_ = ui->editName->text() + ", " + ui->cboLocationName->currentText() + ", " +
				date.toString(Qt::SystemLocaleShortDate) + " " +
				time.toString(Qt::SystemLocaleShortDate) + ", " +
				ui->editUTCOffset->text() + ", " +
				ui->editLat->text() + " " + ui->editLon->text() + " julday " +
				QString::number(tl_.data_[TL_DATETIME], 'f');
	return tl_;
}

void InputForm::setDateTime()
{
	int y, m, d, h, min, s;
    if (sscanf(tl_.str_[TL_DATETIME].toLatin1().constData(), "%d-%02d-%02dT%02d:%02d:%02d", &y, &m, &d, &h, &min, &s) == 6) {
		ui->editDate->setDate(QDate(y, m, d));
		ui->editTime->setTime(QTime(h, min, s));
	}
	else {
		qDebug() << __FUNCTION__ << ": cannot sscanf " << tl_.str_[TL_DATETIME];
	}
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
	NatalConvertor convertor(BaseConvertor::MODE_FROM_ASTROZET, str);
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
		//if (convertor.getString(BaseConvertor::STR_LOCATION_NAME, str))
		//ui->cboLocationName->setItemText(str);
		if (convertor.getString(BaseConvertor::STR_LONGITUDE, str))
			ui->editLon->setText(str);
		if (convertor.getString(BaseConvertor::STR_LATITUDE, str))
			ui->editLat->setText(str);
		if (convertor.getString(BaseConvertor::STR_TZ, str))
			ui->editUTCOffset->setText(str);
	}
}

const QString& InputForm::titleStr() const
{
	return titleStr_;
}
