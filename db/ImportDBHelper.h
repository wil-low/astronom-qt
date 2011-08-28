#ifndef IMPORTDBHELPER_H
#define IMPORTDBHELPER_H

class QString;
class QAbstractItemModel;
class QSqlTableModel;
class QModelIndex;
class TimeLoc;

class ImportDBHelper
{
public:
	ImportDBHelper();
	~ImportDBHelper();
	void createTable (const QString& path);
	QSqlTableModel* model() const;
	bool timeLoc(int record_id, TimeLoc& result) const;
	bool insertTimeLoc(const TimeLoc& tl);
	const char* connectionName() const;
	void clearDB();
	void beginTransaction();
	void commit();
private:
	QSqlTableModel* model_;
};

#endif // IMPORTDBHELPER_H
