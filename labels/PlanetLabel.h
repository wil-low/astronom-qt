#pragma once
#include "AstroLabel.h"

class PlanetLabel : public AstroLabel
{
public:
	PlanetLabel(QWidget* parent, int chart_id, const BodyProps& props);
	virtual ~PlanetLabel(void);
	virtual qreal angle() const;
	virtual qreal visibleAngle() const;

	virtual void setVisibleAngle(qreal ang);
	virtual void setProps(const BodyProps& props);
	PlanetLabel(){}
private:
	qreal visibleLon_;
};
