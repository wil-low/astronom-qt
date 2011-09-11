#ifndef ASPECT_H
#define ASPECT_H

#include <QMetaType>

class BodyProps;
class AspectProps;

class Aspect
{
public:
	Aspect();
	Aspect(double angle, BodyProps* body0, BodyProps* body1,
		   AspectProps* angleProps, AspectProps* signProps);

	void set(double angle, BodyProps* body0, BodyProps* body1,
		   AspectProps* angleProps, AspectProps* signProps);

	QString toString() const;

private:
	double angle_;
	BodyProps* body0_;
	BodyProps* body1_;
	AspectProps* angleProps_;
	AspectProps* signProps_;
};

Q_DECLARE_METATYPE(Aspect)

#endif // ASPECT_H
