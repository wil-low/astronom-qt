#ifndef ASPECT_H
#define ASPECT_H

#include <QMetaType>

class BodyProps;
class AspectProps;

class Aspect
{
public:
	Aspect();
	Aspect(double angle, const BodyProps& body0, const BodyProps& body1,
		   AspectProps* angleProps, AspectProps* signProps);

	void set(double angle, const BodyProps& body0, const BodyProps& body1,
		   AspectProps* angleProps, AspectProps* signProps);

	QString toString() const;

private:
	double angle_;
	int bodyId0_, bodyId1_;
	AspectProps* angleProps_;
	AspectProps* signProps_;
};

Q_DECLARE_METATYPE(Aspect)

#endif // ASPECT_H
