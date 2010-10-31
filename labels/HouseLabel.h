#pragma once
#include "AstroLabel.h"

class HouseLabel : public AstroLabel
{
public:
	HouseLabel(QWidget* parent, int chart_id, const BodyProps& props);
	virtual ~HouseLabel(void);
	virtual qreal angle() const;
	qreal visibleAngle() const;
	HouseLabel(){}
};
