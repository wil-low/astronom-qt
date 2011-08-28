#include "ImportForm.h"
#include "ui_ImportForm.h"
#include "../utils/convertors/NatalConvertor.h"
#include "../utils/TimeLoc.h"
#include "../db/ImportDBHelper.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QSqlTableModel>

ImportForm::ImportForm(QWidget *parent)
: QDialog(parent)
, ui(new Ui::ImportForm)
{
    ui->setupUi(this);
	helper_ = new ImportDBHelper;
	helper_->createTable(":memory:");
	ui->tvEntries->setModel(helper_->model());
}

ImportForm::~ImportForm()
{
	delete helper_;
    delete ui;
}

void ImportForm::on_btnOpenFile_clicked()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setWindowTitle(tr("Open file(s) to import"));
	dialog.setNameFilter(tr("AstroZET database (*.zbs)"));
	QStringList fileNames;
	if (dialog.exec()) {
		helper_->clearDB();
		int counter = 0;
		fileNames = dialog.selectedFiles();
		for (int i = 0; i < fileNames.size(); ++i) {
			QFile file(fileNames[i]);
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				continue;
			helper_->beginTransaction();
			ui->pbImport->setMaximum(0);
			QTextStream in(&file);
			while (!in.atEnd()) {
				if (counter % 10 == 0)
					QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
				QString line = in.readLine();
				NatalConvertor convertor(line, BaseConvertor::MODE_ASTROZET);
				TimeLoc tl(convertor.getString(BaseConvertor::STR_NAME),
						   convertor.getString(BaseConvertor::STR_DATE_TIME),
						   convertor.getString(BaseConvertor::STR_TZ),
						   convertor.getString(BaseConvertor::STR_LOCATION_NAME),
						   convertor.getString(BaseConvertor::STR_LATITUDE),
						   convertor.getString(BaseConvertor::STR_LONGITUDE)
						   );
				tl.recalculate(true);
//				QMessageBox::information(this, "Imported", tl.toString());
				helper_->insertTimeLoc(tl);
				++counter;
				int rowCount = ui->tvEntries->model()->rowCount();
				ui->lblRecordCount->setText(QString::number(rowCount));
				//break;
			}
			helper_->commit();
		}
		ui->pbImport->setMaximum(1);
		int rowCount = ui->tvEntries->model()->rowCount();
		if (rowCount > 0) {
			ui->btnImport->setEnabled(true);
		}
	}
}
