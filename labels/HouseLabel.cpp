#include "HouseLabel.h"
#include "../utils/constants.h"
/*
FXDEFMAP(HouseLabel) PlanetLabelMessageMap[]={

	//________Message_Type_____________________ID____________Message_Handler_______
	FXMAPFUNC(SEL_CLICKED,           0, HouseLabel::onClicked),
};
*/

HouseLabel::HouseLabel(QWidget* parent, int chart_id, const BodyProps& props)
: AstroLabel(parent, chart_id, props)
{
}

HouseLabel::~HouseLabel(void)
{
}

qreal HouseLabel::angle() const
{
	return props_.prop[BodyProps::bp_Lon];
}

qreal HouseLabel::visibleAngle() const
{
	return angle();
}
