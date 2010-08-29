#include "InputForm.h"
#include "ui_InputForm.h"

InputForm::InputForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputForm)
{
    ui->setupUi(this);
}

InputForm::~InputForm()
{
    delete ui;
}

void InputForm::on_btnOK_clicked()
{
	accept();
}

void InputForm::on_btnCancel_clicked()
{
	reject();
}
