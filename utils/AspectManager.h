#ifndef ASPECTMANAGER_H
#define ASPECTMANAGER_H

#include <boost/serialization/singleton.hpp>
#include <map>

class BodyProps;
class AspectProps;
class Aspect;

class AspectManager : public boost::serialization::singleton<AspectManager>
{
public:
    AspectManager();
	void registerProps (int id, double angle, double orb, int signDifference,
						 char angleChar, char signChar);
	void makeAspect (Aspect& aspect, int chart0, const BodyProps& body0, int chart1, const BodyProps& body1) const;
	const AspectProps* getAspect(int id) const;
private:
	int maxAspectId_;
	typedef std::map<int, AspectProps*> AspectPropsMap;
	AspectPropsMap aspectProps_;
};

#endif // ASPECTMANAGER_H
