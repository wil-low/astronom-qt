#include "PersonsForm.h"
#include "ui_PersonsForm.h"
#include "../db/DBHelper.h"

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlError>

#include <QDebug>

PersonsForm::PersonsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonsForm)
{
    ui->setupUi(this);
	ui->tableView->setModel(DBHelper::get_const_instance().personListModel());
}

PersonsForm::~PersonsForm()
{
    delete ui;
}
