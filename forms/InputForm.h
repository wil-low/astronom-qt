#ifndef INPUTFORM_H
#define INPUTFORM_H

#include <QDialog>
#include "../utils/TimeLoc.h"

namespace Ui {
    class InputForm;
}

class InputForm : public QDialog
{
    Q_OBJECT

public:
    explicit InputForm(QWidget *parent = 0);
    ~InputForm();
	void fromTimeLoc (const TimeLoc& tl);
	const TimeLoc& toTimeLoc ();

private:
	void setDateTime(double jday);
    Ui::InputForm *ui;
	TimeLoc tl_;

private slots:
	void on_btnNow_clicked();
	void on_btnCancel_clicked();
	void on_btnOK_clicked();
};

#endif // INPUTFORM_H
