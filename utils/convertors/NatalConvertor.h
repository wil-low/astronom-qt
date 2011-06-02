#ifndef NATALCONVERTOR_H
#define NATALCONVERTOR_H

#include "BaseConvertor.h"
#include <QString>
#include <QDate>
#include <QTime>

class NatalConvertor : public BaseConvertor
{
public:
	NatalConvertor(const QString& input, convert_mode_t mode);
	virtual bool getString(string_val_t type, QString& result);
	virtual bool getDate(datetime_val_t type, QDate& result);
	virtual bool getTime(datetime_val_t type, QTime& result);

private:
	QString name_;
	QDate date_;
	QTime time_;
	QTime utcOffset_;
	QString locationName_;
	QString latStr_;
	QString lonStr_;
};

#endif // NATALCONVERTOR_H
