#include "Aspect.h"
#include "AspectProps.h"
#include "BodyProps.h"

Aspect::Aspect()
: angle_(-1)
, bodyId0_(-1)
, bodyId1_(-1)
, angleProps_(NULL)
, signProps_(NULL)
{
}

Aspect::Aspect(double angle, const BodyProps& body0, const BodyProps& body1,
	   AspectProps* angleProps, AspectProps* signProps)
{
	set (angle, body0, body1, angleProps, signProps);
}

void Aspect::set (double angle, const BodyProps& body0, const BodyProps& body1,
	   AspectProps* angleProps, AspectProps* signProps)
{
	angle_ = angle;
	bodyId0_ = body0.id;
	bodyId1_ = body1.id;
	angleProps_ = angleProps;
	signProps_ = signProps;
}

QString Aspect::toString() const
{
	QString s;
	s.sprintf ("Aspect %X angle %.2f, body0 %d, body1 %d, angleProps %d, signProps %d",
			   this, angle_, bodyId0_, bodyId1_, angleProps_->angleChar(), signProps_->signChar());
	return s;
}
