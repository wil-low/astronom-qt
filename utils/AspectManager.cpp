#include "AspectManager.h"
#include "SettingsManager.h"

#include "utils/BodyProps.h"
#include "utils/AspectProps.h"
#include "utils/Aspect.h"

#include <boost/foreach.hpp>
#include <math.h>

#include <QDebug>

AspectManager::AspectManager()
: maxAspectId_(-1)
{
}

void AspectManager::registerProps (int id, double angle, double orb, int signDifference,
					 char angleChar, char signChar)
{
	AspectPropsMap::iterator it = aspectProps_.find (id);
	if (it == aspectProps_.end()) {
		AspectProps* props = new AspectProps(id, angle, orb, signDifference, angleChar, signChar);
		aspectProps_.insert(std::make_pair(id, props));
		if (id > maxAspectId_)
			maxAspectId_ = id;
	}
	else {
		it->second->set(angle, orb, signDifference, angleChar, signChar);
	}
}

void AspectManager::makeAspect (Aspect& aspect, int chart0, const BodyProps& body0, int chart1, const BodyProps& body1) const
{
	double angle_delta = fabs(body0.prop[BodyProps::bp_Lon] - body1.prop[BodyProps::bp_Lon]);
	if (angle_delta > 180)
		angle_delta = 360 - angle_delta;

	int sign_delta = (int)(body0.prop[BodyProps::bp_Lon] / DEG_PER_SIGN) -
					 (int)(body1.prop[BodyProps::bp_Lon] / DEG_PER_SIGN);
	if (sign_delta < 0)
		sign_delta = -sign_delta;
	if (sign_delta > 6)
		sign_delta = 12 - sign_delta;

	Aspect::Body bodies[2];
	bodies[0].chart_ = chart0;
	bodies[0].id_ = body0.id;
	bodies[0].label_ = SettingsManager::get_const_instance().label(body0);
	bodies[1].chart_ = chart1;
	bodies[1].id_ = body1.id;
	bodies[1].label_ = SettingsManager::get_const_instance().label(body1);
	AspectProps* angleProp = NULL;
	BOOST_FOREACH(const AspectPropsMap::value_type& value, aspectProps_) {
		AspectProps* ap = value.second;
		if (fabs(angle_delta - ap->angle()) < ap->orb()) {
			angleProp = ap;
			break;
		}
	}
	AspectProps* signProp = NULL;
	BOOST_FOREACH(const AspectPropsMap::value_type& value, aspectProps_) {
		AspectProps* ap = value.second;
		if (sign_delta == ap->signDiff()) {
			signProp = ap;
			break;
		}
	}
	//qDebug() << angle_delta << body0.id << body1.id << angle_delta << sign_delta;
	aspect.set (angle_delta, bodies, angleProp, signProp);
}

const AspectProps* AspectManager::getAspect(int id) const
{
	AspectPropsMap::const_iterator it = aspectProps_.find (id);
	if (it == aspectProps_.end())
		return NULL;
	else
		return it->second;
}
