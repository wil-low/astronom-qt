#ifndef DBHELPER_H
#define DBHELPER_H
#include <boost/serialization/singleton.hpp>
class QString;
class QAbstractItemModel;
class QSqlQueryModel;
class QModelIndex;
class TimeLoc;

class DBHelper : public boost::serialization::singleton<DBHelper>
{
public:
    DBHelper();
	~DBHelper();
	void initConnections (const QString& path);
	QAbstractItemModel* personListModel() const;
	bool timeLoc(int record_id, TimeLoc& result) const;

private:
	QSqlQueryModel* personListModel_;
};

#endif // DBHELPER_H
