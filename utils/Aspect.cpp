#include "Aspect.h"

Aspect::Aspect()
: angle_(-1)
, body0_(NULL)
, body1_(NULL)
, angleProps_(NULL)
, signProps_(NULL)
{
}

Aspect::Aspect(double angle, BodyProps* body0, BodyProps* body1,
	   AspectProps* angleProps, AspectProps* signProps)
{
	set (angle, body0, body1, angleProps, signProps);
}

void Aspect::set (double angle, BodyProps* body0, BodyProps* body1,
	   AspectProps* angleProps, AspectProps* signProps)
{
	angle_ = angle;
	body0_ = body0;
	body1_ = body1;
	angleProps_ = angleProps;
	signProps_ = signProps;
}

QString Aspect::toString() const
{
	QString s;
	s.sprintf ("Aspect %X angle %.2f, body0 %X, body1 %X, angleProps %X, signProps %X",
			   this, angle_, body0_, body1_, angleProps_, signProps_);
	return s;
}
