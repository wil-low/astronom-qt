#pragma once

#include <QString>

class DMS 
{
public:
	enum coord_t {
		COORD_UNKNOWN = 0,
		COORD_USE_OWN = 1,
		COORD_LAT = 2,
		COORD_LON = 3,
		COORD_TZ = 4,
	};
	DMS();
	DMS (double angle, coord_t coord_type);
	DMS (const QString& dddmmss, coord_t coord_type);
	void fromCoord (double angle, coord_t coord_type = COORD_USE_OWN);
	void fromCoord (const QString& sdddmmss, coord_t coord_type = COORD_USE_OWN);
	void fromOffset (const QString& sdddmmss);
	QString toMaskedString() const;
	int deg() const;
	int min() const;
	int sec() const;
	int zodiac() const;
	int zod_deg() const;
	double angle() const;

private:
	int deg_, min_, sec_;
	int zodiac_;
	int zod_deg_;
	double angle_;
	coord_t coord_type_;
};
