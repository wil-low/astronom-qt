#include "DBHelper.h"

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQueryModel>

#include <QDebug>

DBHelper::DBHelper()
: personListModel_(NULL)
{
}

DBHelper::~DBHelper()
{
	delete personListModel_;
}

void DBHelper::initConnections (const QString& path)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(path + "/persons.sdb");
	if (db.open() == false)
		qDebug() << "Database error:" << db.lastError().databaseText() << db.lastError().driverText();

	personListModel_ = new QSqlQueryModel;
	personListModel_->setQuery("select NAME, DATE_TIME, LOCATION, LATITUDE, LONGITUDE from TIME_LOCATION");
//	personListModel_->setHeaderData(0, Qt::Horizontal, tr("Name"));
}

QAbstractItemModel* DBHelper::personListModel() const
{
	return personListModel_;
}

