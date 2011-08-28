#include "ImportDBHelper.h"
#include "../utils/TimeLoc.h"
#include "Statements.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>

#include <QDebug>

ImportDBHelper::ImportDBHelper()
: model_(NULL)
{
}

ImportDBHelper::~ImportDBHelper()
{
//	delete personListModel_;
//	QSqlDatabase::removeDatabase(QSqlDatabase::database().connectionName());
}

const char* ImportDBHelper::connectionName() const
{
	return "ImportDBHelper";
}

void ImportDBHelper::createTable (const QString& databaseFilename)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName());
	db.setDatabaseName(databaseFilename);
	if (db.open() == false)
		qDebug() << "Database error:" << db.lastError().databaseText() << db.lastError().driverText();

	QSqlQuery query(CREATE_TABLE_TIME_LOCATION, db);
	model_ = new QSqlTableModel(NULL, db);
	model_->setTable("TIME_LOCATION");
	model_->setEditStrategy(QSqlTableModel::OnManualSubmit);
//	model_->setHeaderData(0, Qt::Horizontal, tr("ID"));
	model_->select();
}

QSqlTableModel* ImportDBHelper::model() const
{
	return model_;
}

bool ImportDBHelper::insertTimeLoc(const TimeLoc& tl)
{
	int row = model_->rowCount();
	model_->insertRows(row, 1);
	model_->setData(model_->index(row, 1), tl.name_);
	model_->setData(model_->index(row, 2), tl.str_[TL_DATETIME]);
	model_->setData(model_->index(row, 3), tl.str_[TL_TZ]);
	model_->setData(model_->index(row, 3), tl.location_);
	model_->setData(model_->index(row, 3), tl.str_[TL_LAT]);
	model_->setData(model_->index(row, 3), tl.str_[TL_LON]);
//	model_->submitAll();
	return true;
}

void ImportDBHelper::beginTransaction()
{
	QSqlDatabase::database(connectionName()).transaction();

}

void ImportDBHelper::commit()
{
	QSqlDatabase::database(connectionName()).commit();
}

void ImportDBHelper::clearDB()
{
	model_->removeRows(0, model_->rowCount());
	model_->submitAll();
}

bool ImportDBHelper::timeLoc(int record_id, TimeLoc& result) const
{
	QSqlQuery query("select ID, NAME, DATE_TIME, TIMEZONE_OFFSET, LOCATION, LATITUDE, LONGITUDE from TIME_LOCATION WHERE ID = ?");
	query.bindValue(0, record_id);
	if (query.exec()) {
		if (query.next()) {
			result = TimeLoc(query.value(1).toString(), query.value(2).toString(), query.value(3).toString(),
							 query.value(4).toString(), query.value(5).toString(), query.value(6).toString());
			return true;
		}
	}
	return false;
}
