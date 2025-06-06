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
	const QString& titleStr() const;

private:
	enum import_mode_t {
		IMPORT_UNKNOWN = -1,
		IMPORT_ASTROZET = 0,
	};

	void setDateTime();
	Ui::InputForm *ui;
	TimeLoc tl_;
	QString titleStr_;
	void import(const QString& str);

private slots:
	void on_btnCopy_clicked();
	void on_btnPaste_clicked();
	void on_btnNow_clicked();
	void on_btnCancel_clicked();
	void on_btnOK_clicked();
};

#endif // INPUTFORM_H
