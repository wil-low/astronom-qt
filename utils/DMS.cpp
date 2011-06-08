#include "DMS.h"
#include "constants.h"
#include <math.h>
#include <stdlib.h>

DMS::DMS()
: deg_(0)
, min_(0)
, sec_(0)
, zodiac_(0)
, zod_deg_(0)
, angle_(0)
, coord_type_(COORD_UNKNOWN)
{
}

DMS::DMS (const QString& dddmmss, coord_t coord_type)
{
	fromCoord (dddmmss, coord_type);
}

DMS::DMS (double angle, coord_t coord_type)
{
	fromCoord (angle, coord_type);
}

void DMS::fromCoord (const QString& sdddmmss, coord_t coord_type)
{
	if (coord_type != COORD_USE_OWN)
		coord_type_ = coord_type;
	int d = sdddmmss.mid(1, 3).toInt();
	int m = sdddmmss.mid(4, 2).toInt();
	int s = sdddmmss.mid(7, 2).toInt();
	int multiplier = 1;
	if (sdddmmss.left(1) == "-")
		multiplier = -1;
	deg_ = d; min_ = m; sec_ = s;
	angle_ = (deg_ + min_ / 60. + sec_ / 3600.) * multiplier;
	zodiac_ = deg_;
	zod_deg_ = int(deg_ - zodiac_ * DEG_PER_SIGN);
}

void DMS::fromOffset (const QString& sdddmmss)
{
	coord_type_ = COORD_TZ;
	int d = sdddmmss.mid(1, 3).toInt();
	int m = sdddmmss.mid(4, 2).toInt();
	int s = sdddmmss.mid(7, 2).toInt();
	int multiplier = 1;
	if (sdddmmss.left(1) == "-")
		multiplier = -1;
	deg_ = d; min_ = m; sec_ = s;
	angle_ = (deg_ * 3600 + min_ * 60 + sec_) * multiplier / SECONDS_IN_DAY;
}

void DMS::fromCoord (double angle, coord_t coord_type)
{
	if (coord_type != COORD_USE_OWN)
		coord_type_ = coord_type;
	angle_ = angle;
	deg_ = int(angle);
	angle = fabs(angle);
	angle -= abs(deg_);
	angle *= 60;
	min_ = int(angle);
	angle -= min_;
	angle *= 60;
	sec_ = int(angle);
	angle = deg_ / DEG_PER_SIGN;
	zodiac_ = int(angle);
	zod_deg_ = int(deg_ - zodiac_ * DEG_PER_SIGN);
}

int DMS::deg() const
{
	return deg_;
}

int DMS::min() const
{
	return min_;
}

int DMS::sec() const
{
	return sec_;
}

int DMS::zodiac() const
{
	return zodiac_;
}

int DMS::zod_deg() const
{
	return zod_deg_;
}

double DMS::angle() const
{
	return angle_;
}

QString DMS::toMaskedString() const
{
	QString s;
	switch (coord_type_) {
	case COORD_LAT:
		s.sprintf ("%03d%02d%02d%c", abs(deg_), min_, sec_, deg_ >= 0 ? 'N' : 'S');
		break;
	case COORD_LON:
		s.sprintf ("%03d%02d%02d%c", abs(deg_), min_, sec_, deg_ >= 0 ? 'E' : 'W');
		break;
	case COORD_TZ:
		s.sprintf ("%c%03d%02d%02d", (deg_ >= 0 ? '+' : '-'), abs(deg_), min_, sec_);
		break;
	}

	return s;
}

