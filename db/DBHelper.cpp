#include "DBHelper.h"
#include "../utils/TimeLoc.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>

#include <QDebug>

DBHelper::DBHelper()
: personListModel_(NULL)
{
}

DBHelper::~DBHelper()
{
//	delete personListModel_;
//	QSqlDatabase::removeDatabase(QSqlDatabase::database().connectionName());
}

void DBHelper::initConnections (const QString& path)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(path + "/persons.sdb");
	if (db.open() == false)
		qDebug() << "Database error:" << db.lastError().databaseText() << db.lastError().driverText();

	personListModel_ = new QSqlTableModel();
	personListModel_->setTable("TIME_LOCATION");
	personListModel_->setEditStrategy(QSqlTableModel::OnManualSubmit);
	personListModel_->setSort(personListModel_->fieldIndex("NAME"), Qt::AscendingOrder);
	personListModel_->select();
//	personListModel_->setHeaderData(0, Qt::Horizontal, tr("Name"));
}

QSqlTableModel* DBHelper::personListModel() const
{
	return personListModel_;
}

bool DBHelper::timeLoc(int record_id, TimeLoc& result) const
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
