#include "InputForm.h"
#include "ui_InputForm.h"
#include "../utils/Ephemeris.h"
#include "../utils/DMS.h"

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
