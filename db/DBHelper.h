#ifndef DBHELPER_H
#define DBHELPER_H
#include <boost/serialization/singleton.hpp>
class QString;
class QAbstractItemModel;
class QSqlTableModel;
class QModelIndex;
class TimeLoc;

class DBHelper : public boost::serialization::singleton<DBHelper>
{
public:
    DBHelper();
	~DBHelper();
	void initConnections (const QString& path);
	QSqlTableModel* personListModel() const;
	bool timeLoc(int record_id, TimeLoc& result) const;

private:
	QSqlTableModel* personListModel_;
};

#endif // DBHELPER_H
