#ifndef DBHELPER_H
#define DBHELPER_H
#include <boost/serialization/singleton.hpp>

class QString;
class QAbstractItemModel;
class QSqlQueryModel;

class DBHelper : public boost::serialization::singleton<DBHelper>
{
public:
    DBHelper();
	~DBHelper();
	void initConnections (const QString& path);
	QAbstractItemModel* personListModel() const;

private:
	QSqlQueryModel* personListModel_;
};

#endif // DBHELPER_H
