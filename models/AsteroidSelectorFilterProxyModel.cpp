#include "AsteroidSelectorFilterProxyModel.h"
#include "../utils/BodyProps.h"

const int LAST_MAIN_PLANET = 9;

AsteroidSelectorMainFilterModel::AsteroidSelectorMainFilterModel(QObject *parent, QAbstractItemModel* model)
: QSortFilterProxyModel(parent)
{
	setSourceModel(model);
}

bool AsteroidSelectorMainFilterModel::filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const
{
	QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    BodyProps props = index0.data().value<BodyProps>();
	return (props.type == TYPE_ASTEROID);
}

//------------------------------------------------------

AsteroidSelectorSecondaryFilterModel::AsteroidSelectorSecondaryFilterModel(QObject *parent, QAbstractItemModel* model)
: QSortFilterProxyModel(parent)
{
	setSourceModel(model);
}

bool AsteroidSelectorSecondaryFilterModel::filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const
{
	QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    BodyProps props = index0.data().value<BodyProps>();
	return false; //(props.type == TYPE_ASTEROID);
}
