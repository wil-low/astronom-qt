#ifndef ASPECT_H
#define ASPECT_H

#include <QMetaType>

class AspectProps;

class Aspect
{
public:
	struct Body {
		int chart_;
		int id_;
		QString label_;
		Body() : chart_(-1), id_(-1) {}
	};
	Aspect();
	Aspect(double angle, const Body* bodies, AspectProps* angleProps, AspectProps* signProps);
	void set(double angle, const Body* bodies, AspectProps* angleProps, AspectProps* signProps);
	double angle_;
	Body body_[2];
	AspectProps* angleProps_;
	AspectProps* signProps_;
};

Q_DECLARE_METATYPE(Aspect)

#endif // ASPECT_H
