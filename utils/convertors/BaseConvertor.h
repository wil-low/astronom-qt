#ifndef BASECONVERTOR_H
#define BASECONVERTOR_H

class QDate;
class QTime;
class QString;

class BaseConvertor
{
public:
	enum convert_mode_t {
		MODE_UNDEF = 0,
		MODE_FROM_ASTROZET = 1,
		MODE_TO_ASTROZET = 2,
	};

	enum string_val_t {
		STR_NAME = 0,
		STR_LOCATION_NAME,
		STR_LATITUDE,
		STR_LONGITUDE,
		STR_TZ,
		STR_DATE_TIME,
		STR_TO_ASTROZET,
		STR_LAST,
	};

	enum coord_val_t {
		COORD_LATITUDE = 0,
		COORD_LONGITUDE,
		COORD_LAST,
	};

	enum datetime_val_t {
		DT_NATAL_DATE = 0,
		DT_NATAL_TIME,
		DT_UTC_OFFSET,
		DT_LAST,
	};

	BaseConvertor();
	BaseConvertor(convert_mode_t mode);
	
	virtual bool setString(string_val_t type, const QString& str) {return false;}

	virtual bool getString(string_val_t type, QString& result) {return false;}
	virtual bool getDate(datetime_val_t type, QDate& result) {return false;}
	virtual bool getTime(datetime_val_t type, QTime& result) {return false;}
	virtual bool getDouble(coord_val_t type, double& result) {return false;}

	virtual bool isValid() {return isValid_;}

protected:
	bool isValid_;
	convert_mode_t mode_;
};

#endif // BASECONVERTOR_H
