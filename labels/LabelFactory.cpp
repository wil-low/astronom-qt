#include "LabelFactory.h"
#include "AstroLabel.h"
#include "ZodiacLabel.h"
#include "PlanetLabel.h"

LabelFactory::LabelFactory()
{
}

AstroLabel* LabelFactory::construct(QWidget* parent, int chart_id, const BodyProps& props)
{
	AstroLabel* label = NULL;
	switch (props.type) {
	case TYPE_ZODIAC:
		label = new ZodiacLabel(parent, chart_id, props);
		break;
	case TYPE_PLANET:
		label = new PlanetLabel(parent, chart_id, props);
		break;
	}
	return label;
}
