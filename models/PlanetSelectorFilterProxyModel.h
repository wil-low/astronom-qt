#ifndef PLANETSELECTORFILTERPROXYMODEL_H
#define PLANETSELECTORFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class PlanetSelectorMainFilterModel : public QSortFilterProxyModel
{
public:
	PlanetSelectorMainFilterModel(QObject* parent, QAbstractItemModel* model);
protected:
	virtual bool filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const;
};

class PlanetSelectorSecondaryFilterModel : public QSortFilterProxyModel
{
public:
	PlanetSelectorSecondaryFilterModel(QObject* parent, QAbstractItemModel* model);
protected:
	virtual bool filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const;
};

#endif // PLANETSELECTORFILTERPROXYMODEL_H
