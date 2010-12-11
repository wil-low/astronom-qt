#include "DMS.h"
#include "constants.h"
#include <math.h>
#include <stdlib.h>

DMS::DMS()
: deg_(0), min_(0), sec_(0), zodiac_(0), zod_deg_(0), angle_(0)
{
}

DMS::DMS (const QString& dddmmss)
{
	calculate (dddmmss);
}

DMS::DMS (double angle)
{
	calculate (angle);
}

void DMS::calculate (const QString& dddmmss)
{
	int d = dddmmss.left(3).toInt();
	int m = dddmmss.mid(3, 2).toInt();
	int s = dddmmss.mid(6, 2).toInt();
	deg_ = d; min_ = m; sec_ = s;
	angle_ = deg_ + min_ / 60. + sec_ / 3600.;
	zodiac_ = int(angle_);
	zod_deg_ = int(deg_ - zodiac_ * DEG_PER_SIGN);
}

void DMS::calculate (double angle)
{
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
	s.sprintf ("%3d%2d%2d", deg_, min_, sec_);
	return s;
}

