#ifndef BASECONVERTOR_H
#define BASECONVERTOR_H

class QDate;
class QTime;
class QString;

class BaseConvertor
{
public:
	enum convert_mode_t {
		MODE_ASTROZET = 0,
	};

	enum string_val_t {
		STR_NAME = 0,
		STR_LOCATION_NAME,
		STR_LATITUDE,
		STR_LONGITUDE,
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

	virtual bool getString(string_val_t type, QString& result) {return false;}
	virtual bool getDate(datetime_val_t type, QDate& result) {return false;}
	virtual bool getTime(datetime_val_t type, QTime& result) {return false;}
	virtual bool getCoord(coord_val_t type, double& result) {return false;}

	virtual bool isValid() {return isValid_;}

protected:
	bool isValid_;
};

#endif // BASECONVERTOR_H
