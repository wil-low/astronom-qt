#include "PlanetSelectorFilterProxyModel.h"
#include "../utils/BodyProps.h"

const int LAST_MAIN_PLANET = 9;

PlanetSelectorMainFilterModel::PlanetSelectorMainFilterModel(QObject *parent, QAbstractItemModel* model)
: QSortFilterProxyModel(parent)
{
	setSourceModel(model);
}

bool PlanetSelectorMainFilterModel::filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const
{
	QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
	BodyProps props = qVariantValue<BodyProps>(index0.data());
	return (props.type == TYPE_PLANET && props.id <= LAST_MAIN_PLANET);
}

//------------------------------------------------------

PlanetSelectorSecondaryFilterModel::PlanetSelectorSecondaryFilterModel(QObject *parent, QAbstractItemModel* model)
: QSortFilterProxyModel(parent)
{
	setSourceModel(model);
}

bool PlanetSelectorSecondaryFilterModel::filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const
{
	QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
	BodyProps props = qVariantValue<BodyProps>(index0.data());
	return (props.type == TYPE_PLANET && props.id > LAST_MAIN_PLANET);
}
