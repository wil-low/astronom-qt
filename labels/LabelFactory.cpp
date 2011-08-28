#include "LabelFactory.h"
#include "AstroLabel.h"
#include "ZodiacLabel.h"
#include "PlanetLabel.h"
#include "HouseLabel.h"
#include "AspectLabel.h"
#include "ReferenceLabel.h"

#include <assert.h>

LabelFactory::LabelFactory()
{
}

AstroLabel* LabelFactory::construct(QWidget* parent, int chart_id, const BodyProps& props)
{
	assert(props.id != -1 && "id == -1");
	AstroLabel* label = NULL;
	switch (props.type) {
	case TYPE_ZODIAC:
		label = new ZodiacLabel(parent, chart_id, props);
		break;
	case TYPE_PLANET:
		label = new PlanetLabel(parent, chart_id, props);
		break;
	case TYPE_HOUSE:
		label = new HouseLabel(parent, chart_id, props);
		break;
	case TYPE_ASPECT:
		label = new AspectLabel(parent, chart_id, props);
		break;
	case TYPE_REFERENCE:
		label = new ReferenceLabel(parent, chart_id, props);
		break;
	}
	return label;
}
