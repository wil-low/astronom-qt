#include "AsteroidSelector.h"
#include "../models/AsteroidSelectorFilterProxyModel.h"

AsteroidSelector::AsteroidSelector(QWidget *parent, QAbstractItemModel* model)
: BodySelector(parent, model)
{
}

QSortFilterProxyModel* AsteroidSelector::getFilterModel(BaseSelector::model_t modelType)
{
	if (modelType == MODEL_MAIN)
		return new AsteroidSelectorMainFilterModel(this, model_);
	else
		return new AsteroidSelectorSecondaryFilterModel(this, model_);
}

