#include "PersonsForm.h"
#include "ui_PersonsForm.h"
#include "../db/DBHelper.h"
#include "../utils/TimeLoc.h"

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlError>

#include <QDebug>

PersonsForm::PersonsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonsForm)
{
    ui->setupUi(this);
	ui->tvPersonList->setModel(DBHelper::get_const_instance().personListModel());
}

PersonsForm::~PersonsForm()
{
    delete ui;
}

void PersonsForm::on_tvPersonList_doubleClicked(const QModelIndex& index)
{
	TimeLoc tl;
	QModelIndex idx = index.model()->index(index.row(), 0, ui->tvPersonList->rootIndex());
	if (DBHelper::get_const_instance().timeLoc(index.model()->data(idx).toLongLong(), tl)) {
		tl.recalculate(true);
		qDebug() << tl;
		emit timeloc_set(tl);
		hide();
	}
}
