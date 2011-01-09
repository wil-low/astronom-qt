#include "FormulaForm.h"
#include "ui_FormulaForm.h"
#include "../utils/FormulaHelper.h"

FormulaForm::FormulaForm(QWidget *parent)
: QDialog(parent)
, ui(new Ui::FormulaForm)
, helper_(new FormulaHelper)
{
    ui->setupUi(this);
}

FormulaForm::~FormulaForm()
{
    delete ui;
	delete helper_;
}

void FormulaForm::setVariable (const QString& name, double val)
{
	helper_->setVariable(name, val);
}

void FormulaForm::on_btnEval_clicked()
{
	ui->txtFormulaResult->setPlainText(helper_->evaluate (ui->txtFormula->toPlainText()));
}
