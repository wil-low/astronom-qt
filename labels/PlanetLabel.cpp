#include "PlanetLabel.h"

PlanetLabel::PlanetLabel(QWidget* parent, int chart_id, const BodyProps& props)
: AstroLabel(parent, chart_id, props)
{
}

PlanetLabel::~PlanetLabel(void)
{
}

qreal PlanetLabel::angle() const
{
	return props_.prop[BodyProps::bp_Lon];
}

qreal PlanetLabel::visibleAngle() const
{
	return visibleLon_;
}

void PlanetLabel::setVisibleAngle(qreal ang)
{
    visibleLon_ = ang;
}

void PlanetLabel::setProps(const BodyProps& props)
{
	AstroLabel::setProps(props);
	if (props_.prop[BodyProps::bp_LonSpeed] < -STABLESPEED)
		flags_ |= af_Retrograde;
}
