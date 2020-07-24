#include "NatalConvertor.h"
#include <QTextCodec>
#include <QRegExp>
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
		QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
        QString decodedStr = codec->toUnicode(input.toLatin1());
		//QMessageBox::warning(this, "Has text", decodedStr);
		QStringList values = decodedStr.split(';');
		if (values.size() < 7)
			return;
		name_ = values[0];
                QRegExp rx("(\\d+)\\.(\\d+)\\.(\\d+)");
		if (rx.indexIn(values[1]) != -1) {
			date_ = QDate(rx.cap(3).toInt(), rx.cap(2).toInt(), rx.cap(1).toInt());
		}
		rx.setPattern("(\\d+):(\\d+):(\\d+)");
		if (rx.indexIn(values[2]) != -1) {
			time_ = QTime(rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt());
		}
		dateTimeStr_ = QDateTime(date_, time_).toString(Qt::ISODate);

                rx.setPattern("([\\+\\-]\\d+):(\\d+)(?::(\\d+))?");
		if (rx.indexIn(values[3]) != -1) {
			utcOffsetStr_.sprintf("%02d%02d%02d",
							rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt());
			utcOffset_ = QTime(rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt());
		}
		locationName_ = values[4];
		rx.setPattern("(\\d+)°(\\d+)'(\\d+)\"([NS])");
		if (rx.indexIn(values[5]) != -1) {
			latStr_.sprintf("%03d%02d%02d",
							rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt());
			latStr_ += rx.cap(4);
		}
		else {
			qDebug() << "Cannot match " << values[5];
		}
		rx.setPattern("(\\d+)°(\\d+)'(\\+)\"([EW])d");
		if (rx.indexIn(values[6]) != -1) {
			lonStr_.sprintf("%03d%02d%02d",
							rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt());
			lonStr_ += rx.cap(4);
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
