#include "ZodiacLabel.h"
#include "../utils/constants.h"
/*
FXDEFMAP(ZodiacLabel) PlanetLabelMessageMap[]={

	//________Message_Type_____________________ID____________Message_Handler_______
	FXMAPFUNC(SEL_CLICKED,           0, ZodiacLabel::onClicked),
};
*/

ZodiacLabel::ZodiacLabel(QWidget* parent, int chart_id, const BodyProps& props)
: AstroLabel(parent, chart_id, props)
{
}

ZodiacLabel::~ZodiacLabel(void)
{
}

qreal ZodiacLabel::angle() const
{
	return props_.id * DEG_PER_SIGN + DEG_PER_SIGN / 2;
}

qreal ZodiacLabel::visibleAngle() const
{
	return angle();
}
