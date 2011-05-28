#include "PlanetSelector.h"
#include "BodySelectorDelegate.h"
#include "../models/PlanetSelectorFilterProxyModel.h"

PlanetSelector::PlanetSelector(QWidget *parent, QAbstractItemModel* model)
: BodySelector(parent, model)
{
}

QSortFilterProxyModel* PlanetSelector::getFilterModel(BaseSelector::model_t modelType)
{
	if (modelType == MODEL_MAIN)
		return new PlanetSelectorMainFilterModel(this, model_);
	else
		return new PlanetSelectorSecondaryFilterModel(this, model_);
}
