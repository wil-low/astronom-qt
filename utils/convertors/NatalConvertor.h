#ifndef NATALCONVERTOR_H
#define NATALCONVERTOR_H

#include "BaseConvertor.h"
#include <QString>
#include <QDate>
#include <QTime>

class NatalConvertor : public BaseConvertor
{
public:
	NatalConvertor(convert_mode_t mode);
	NatalConvertor(convert_mode_t mode, const QString& input);
	
	virtual bool setString(string_val_t type, const QString& str);
	
	virtual bool getString(string_val_t type, QString& result);
	virtual bool getDate(datetime_val_t type, QDate& result);
	virtual bool getTime(datetime_val_t type, QTime& result);
	const QString& getString(string_val_t type);
private:
	QString name_;
	QDate date_;
	QTime time_;
	QTime utcOffset_;
	QString locationName_;
	QString latStr_;
	QString lonStr_;
	QString dateTimeStr_;
	QString utcOffsetStr_;
};

#endif // NATALCONVERTOR_H
