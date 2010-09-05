#include "ZodiacLabel.h"
#include "../utils/constants.h"
/*
FXDEFMAP(ZodiacLabel) PlanetLabelMessageMap[]={

	//________Message_Type_____________________ID____________Message_Handler_______
	FXMAPFUNC(SEL_CLICKED,           0, ZodiacLabel::onClicked),
};
*/

ZodiacLabel::ZodiacLabel(int sign, QWidget* p)
: AstroLabel(p)
, sign_(sign)
{
}

ZodiacLabel::~ZodiacLabel(void)
{
}

qreal ZodiacLabel::angle() const
{
	return sign_ * DEG_PER_SIGN + DEG_PER_SIGN / 2;
}

qreal ZodiacLabel::visibleAngle() const
{
	return angle();
}

body_type_t ZodiacLabel::type() const
{
    return TYPE_ZODIAC;
}
