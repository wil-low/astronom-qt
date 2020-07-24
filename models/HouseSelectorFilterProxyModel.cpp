#include "HouseSelectorFilterProxyModel.h"
#include "../utils/BodyProps.h"

const int LAST_MAIN_PLANET = 9;

HouseSelectorMainFilterModel::HouseSelectorMainFilterModel(QObject *parent, QAbstractItemModel* model)
: QSortFilterProxyModel(parent)
{
	setSourceModel(model);
}

bool HouseSelectorMainFilterModel::filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const
{
	QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    BodyProps props = index0.data().value<BodyProps>();
	return (props.type == TYPE_HOUSE);
}

//------------------------------------------------------

HouseSelectorSecondaryFilterModel::HouseSelectorSecondaryFilterModel(QObject *parent, QAbstractItemModel* model)
: QSortFilterProxyModel(parent)
{
	setSourceModel(model);
}

bool HouseSelectorSecondaryFilterModel::filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const
{
	QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    BodyProps props = index0.data().value<BodyProps>();
	return (props.type == TYPE_HOUSE);
}
