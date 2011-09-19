#include "Aspect.h"
#include "AspectProps.h"

Aspect::Aspect()
: angle_(-1)
, angleProps_(NULL)
, signProps_(NULL)
{
}

Aspect::Aspect(double angle, const Aspect::Body* bodies, AspectProps* angleProps, AspectProps* signProps)
{
	set (angle, bodies, angleProps, signProps);
}

void Aspect::set (double angle, const Aspect::Body* bodies, AspectProps* angleProps, AspectProps* signProps)
{
	angle_ = angle;
	body_[0] = bodies[0];
	body_[1] = bodies[1];
	angleProps_ = angleProps;
	signProps_ = signProps;
}
