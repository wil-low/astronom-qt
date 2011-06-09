#include "PersonsForm.h"
#include "ui_PersonsForm.h"
#include "../db/DBHelper.h"
#include "../utils/TimeLoc.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>

#include <QDebug>
#include <QDataWidgetMapper>

PersonsForm::PersonsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonsForm)
{
    ui->setupUi(this);
	ui->editLat->setCoordType(DMS::COORD_LAT);
	ui->editLon->setCoordType(DMS::COORD_LON);

	QSqlTableModel* model = DBHelper::get_const_instance().personListModel();
	ui->lvPersons->setModel(model);
	ui->lvPersons->setModelColumn(1); // NAME
	ui->tvPersonList->setModel(model);

	QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
	mapper->setModel(model);
//	mapper->setItemDelegate(new BookDelegate(this));
	mapper->addMapping(ui->editLat, model->fieldIndex("LATITUDE"), "dbText");
	mapper->addMapping(ui->editLon, model->fieldIndex("LONGITUDE"), "dbText");
	mapper->addMapping(ui->editDateTime, model->fieldIndex("DATE_TIME"));
	mapper->addMapping(ui->editTimeOffset, model->fieldIndex("TIMEZONE_OFFSET"), "dbText");

	connect(ui->lvPersons->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
			mapper, SLOT(setCurrentModelIndex(QModelIndex)));
	ui->lvPersons->setCurrentIndex(model->index(0, 0));
}

PersonsForm::~PersonsForm()
{
    delete ui;
}

void PersonsForm::on_lvPersons_doubleClicked(const QModelIndex& index)
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
