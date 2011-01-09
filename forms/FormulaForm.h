#ifndef FORMULAFORM_H
#define FORMULAFORM_H

#include <QDialog>

namespace Ui {
    class FormulaForm;
}

class FormulaHelper;

class FormulaForm : public QDialog
{
    Q_OBJECT

public:
    explicit FormulaForm(QWidget *parent = 0);
    ~FormulaForm();
	void setVariable (const QString& name, double val);

private:
    Ui::FormulaForm *ui;
	FormulaHelper* helper_;

private slots:
	void on_btnEval_clicked();
};

#endif // FORMULAFORM_H
