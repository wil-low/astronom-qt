#include "NatalConvertor.h"
#include <QTextCodec>
#include <QRegExp>
#include <QStringList>

NatalConvertor::NatalConvertor(const QString& input, BaseConvertor::convert_mode_t mode)
: BaseConvertor()
{
	switch (mode) {
	case MODE_ASTROZET:
		QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
		QString decodedStr = codec->toUnicode(input.toAscii());
		//QMessageBox::warning(this, "Has text", decodedStr);
		QStringList values = decodedStr.split(';');
		if (values.size() < 7)
			return;
		name_ = values[0];
		QRegExp rx("(\\d+)\.(\\d+)\.(\\d+)");
		if (rx.indexIn(values[1]) != -1) {
			date_ = QDate(rx.cap(3).toInt(), rx.cap(2).toInt(), rx.cap(1).toInt());
		}
		rx.setPattern("(\\d+):(\\d+):(\\d+)");
		if (rx.indexIn(values[2]) != -1) {
			time_ = QTime(rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt());
		}
		rx.setPattern("([\+\-]\\d+):(\\d+):(\\d+)");
		if (rx.indexIn(values[3]) != -1) {
			utcOffset_ = QTime(rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt());
		}
		locationName_ = values[4];
		lonStr_ = values[5];
		latStr_ = values[6];
		isValid_ = true;
	}
}

bool NatalConvertor::getString(string_val_t type, QString& result)
{
	bool isSet = false;
	if (isValid_) {
		switch (type) {
		case STR_NAME:
			result = name_; isSet = true; break;
		case STR_LOCATION_NAME:
			result = locationName_; isSet = true; break;
		case STR_LATITUDE:
			result = latStr_; isSet = true; break;
		case STR_LONGITUDE:
			result = lonStr_; isSet = true; break;
		}
	}
	return isSet;
}

bool NatalConvertor::getDate(datetime_val_t type, QDate& result)
{
	bool isSet = false;
	if (isValid_) {
		switch (type) {
		case DT_NATAL_DATE:
			result = date_; isSet = true; break;
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
			result = time_; isSet = true; break;
		case DT_UTC_OFFSET:
			result = utcOffset_; isSet = true; break;
		}
	}
	return isSet;
}

