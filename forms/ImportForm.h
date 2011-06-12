#ifndef IMPORT_FORM_H
#define IMPORT_FORM_H

#include <QDialog>

class ImportDBHelper;

namespace Ui {
	class ImportForm;
}

class ImportForm : public QDialog
{
    Q_OBJECT

public:
	explicit ImportForm(QWidget *parent = 0);
	~ImportForm();

private:
	enum import_mode_t {
		IMPORT_UNKNOWN = -1,
		IMPORT_ASTROZET = 0,
	};
	Ui::ImportForm *ui;
	ImportDBHelper* helper_;

private slots:

private slots:
	void on_btnOpenFile_clicked();
};

#endif // IMPORT_FORM_H
