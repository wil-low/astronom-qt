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
	visible_ = false;
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

void HouseLabel::setProps(const BodyProps& props)
{
	AstroLabel::setProps(props);
	int cusp_count = props_.userData;
	astro_flag_t af = af_Undef;
	int id0 = id() - HOUSE_ID_FIRST;
	if (id0 >= 0) {
		if (id0 == 0 * cusp_count / 4)
			af = af_Asc;
		else if (id0 == 1 * cusp_count / 4)
			af = af_IC;
		else if (id0 == 2 * cusp_count / 4)
			af = af_Dsc;
		else if (id0 == 3 * cusp_count / 4)
			af = af_MC;
	}
	flags_ = af;
}
