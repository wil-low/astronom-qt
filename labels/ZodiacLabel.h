#pragma once
#include "AstroLabel.h"

class ZodiacLabel : public AstroLabel
{
public:
	ZodiacLabel(QWidget* parent, int chart_id, const BodyProps& props);
	virtual ~ZodiacLabel(void);
	virtual qreal angle() const;
	qreal visibleAngle() const;
	ZodiacLabel(){}
};
