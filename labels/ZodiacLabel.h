#pragma once
#include "AstroLabel.h"

class ZodiacLabel : public AstroLabel
{
public:
	ZodiacLabel(int sign, QWidget* p);
	virtual ~ZodiacLabel(void);
	virtual qreal angle() const;
	virtual body_type_t type() const;
	qreal visibleAngle() const;
	ZodiacLabel(){}
private:
    int sign_;
};
