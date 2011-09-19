#include "AspectManager.h"

#include "utils/BodyProps.h"
#include "utils/AspectProps.h"
#include "utils/Aspect.h"

#include <boost/foreach.hpp>
#include <math.h>

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

bool AspectManager::makeAspect (Aspect& aspect, const BodyProps& body0, const BodyProps& body1) const
{
	double angle_delta = fabs(body0.prop[BodyProps::bp_Lon] - body1.prop[BodyProps::bp_Lon]);
	BOOST_FOREACH(const AspectPropsMap::value_type value, aspectProps_) {
		if (fabs(angle_delta - value.second->angle()) < value.second->orb()) {
			aspect.set (angle_delta, body0, body1, value.second, value.second);
			return true;
		}
	}
	return false;
}

const AspectProps* AspectManager::getAspect(int id) const
{
	AspectPropsMap::const_iterator it = aspectProps_.find (id);
	if (it == aspectProps_.end())
		return NULL;
	else
		return it->second;
}
