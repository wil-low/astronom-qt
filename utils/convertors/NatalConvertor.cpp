#include "NatalConvertor.h"
#include <QStringDecoder>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QStringList>
#include <QDebug>

NatalConvertor::NatalConvertor(BaseConvertor::convert_mode_t mode)
: BaseConvertor(mode)
{
	switch (mode_) {
	case MODE_TO_ASTROZET:
		break;
	}
}

NatalConvertor::NatalConvertor(BaseConvertor::convert_mode_t mode, const QString& input)
: BaseConvertor(mode)
{
	switch (mode_) {
	case MODE_FROM_ASTROZET:
        QStringDecoder decoder("Windows-1251");
        QString decodedStr = decoder.decode(input.toLatin1());
        //QMessageBox::warning(this, "Has text", decodedStr);
		QStringList values = decodedStr.split(';');
		if (values.size() < 7)
			return;
		name_ = values[0];
        QRegularExpression dateRx(R"((\d+)\.(\d+)\.(\d+))");
        QRegularExpressionMatch dateMatch = dateRx.match(values[1]);
        if (dateMatch.hasMatch()) {
            date_ = QDate(
                dateMatch.captured(3).toInt(),
                dateMatch.captured(2).toInt(),
                dateMatch.captured(1).toInt()
                );
        }
        QRegularExpression timeRx(R"((\d+):(\d+):(\d+))");
        QRegularExpressionMatch timeMatch = timeRx.match(values[2]);
        if (timeMatch.hasMatch()) {
            time_ = QTime(
                timeMatch.captured(1).toInt(),
                timeMatch.captured(2).toInt(),
                timeMatch.captured(3).toInt()
                );
        }
		dateTimeStr_ = QDateTime(date_, time_).toString(Qt::ISODate);
        
        QRegularExpression offsetRx(R"(([\\+\\-]\\d+):(\\d+)(?::(\\d+))?)");
        QRegularExpressionMatch offsetMatch = offsetRx.match(values[3]);
        if (offsetMatch.hasMatch()) {
            utcOffsetStr_.asprintf("%02d%02d%02d",
                offsetMatch.captured(1).toInt(),
                offsetMatch.captured(2).toInt(),
                offsetMatch.captured(3).toInt()
                );
            utcOffset_ = QTime(
                offsetMatch.captured(1).toInt(),
                offsetMatch.captured(2).toInt(),
                offsetMatch.captured(3).toInt()
                );
        }
		locationName_ = values[4];

        QRegularExpression latRx(R"((\\d+)°(\\d+)'(\\d+)\"([NS]))");
        QRegularExpressionMatch latMatch = latRx.match(values[5]);
        if (latMatch.hasMatch()) {
            latStr_.asprintf("%03d%02d%02d",
                latMatch.captured(1).toInt(),
                latMatch.captured(2).toInt(),
                latMatch.captured(3).toInt()
                );
            latStr_ = latMatch.captured(4);
        }
        else {
            qDebug() << "Cannot match " << values[5];
        }
        
        QRegularExpression lonRx(R"((\\d+)°(\\d+)'(\\+)\"([EW])d)");
        QRegularExpressionMatch lonMatch = lonRx.match(values[6]);
        if (lonMatch.hasMatch()) {
            lonStr_.asprintf("%03d%02d%02d",
                             lonMatch.captured(1).toInt(),
                             lonMatch.captured(2).toInt(),
                             lonMatch.captured(3).toInt()
                             );
            lonStr_ = lonMatch.captured(4);
        }
        else {
            qDebug() << "Cannot match " << values[6];
        }
		isValid_ = true;
	}
}

bool NatalConvertor::getString(string_val_t type, QString& result)
{
	if (isValid_) {
		result = getString(type);
	}
	return isValid_;
}

const QString& NatalConvertor::getString(string_val_t type)
{
	if (isValid_) {
		switch (type) {
		case STR_NAME:
			return name_;
		case STR_LOCATION_NAME:
			return locationName_;
		case STR_LATITUDE:
			return latStr_;
		case STR_LONGITUDE:
			return lonStr_;
		case STR_DATE_TIME:
			return dateTimeStr_;
		case STR_TZ:
			return utcOffsetStr_;
		}
	}
	return "";
}

bool NatalConvertor::getDate(datetime_val_t type, QDate& result)
{
	bool isSet = false;
	if (isValid_) {
		switch (type) {
		case DT_NATAL_DATE:
			result = date_; isSet = true;
			break;
		}
	}
	return isSet;
}

bool NatalConvertor::getTime(datetime_val_t type, QTime& result)
{
	bool isSet = false;
	if (isValid_) {
		switch (type) {
		case DT_NATAL_TIME:
			result = time_; isSet = true;
			break;
		case DT_UTC_OFFSET:
			result = utcOffset_; isSet = true;
			break;
		}
	}
	return isSet;
}

bool NatalConvertor::setString(string_val_t type, const QString& str)
{
	
}
