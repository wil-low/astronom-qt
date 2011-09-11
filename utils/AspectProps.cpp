#include "AspectProps.h"

AspectProps::AspectProps()
: id_(-1)
, angle_(-1)
, orb_(-1)
, signDiff_(-1)
, angleChar_(0)
, signChar_(0)
{
}

AspectProps::AspectProps(int id, double angle, double orb, int signDiff,
						 char angleChar, char signChar)
: id_(id)
{
	set(angle, orb, signDiff, angleChar, signChar);
}

void AspectProps::set(double angle, double orb, int signDiff,
					  char angleChar, char signChar)
{
	angle_ = angle;
	orb_ = orb;
	signDiff_ = signDiff;
	angleChar_ = angleChar;
	signChar_ = signChar;
}

int AspectProps::id() const
{
	return id_;
}

double AspectProps::angle() const
{
	return angle_;
}

double AspectProps::orb() const
{
	return orb_;
}

int AspectProps::signDiff() const
{
	return signDiff_;
}

char AspectProps::angleChar() const
{
	return angleChar_;
}

char AspectProps::signChar() const
{
	return signChar_;
}
