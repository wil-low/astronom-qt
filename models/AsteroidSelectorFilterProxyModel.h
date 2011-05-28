#ifndef AsteroidSelectorFILTERPROXYMODEL_H
#define AsteroidSelectorFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class AsteroidSelectorMainFilterModel : public QSortFilterProxyModel
{
public:
	AsteroidSelectorMainFilterModel(QObject* parent, QAbstractItemModel* model);
protected:
	virtual bool filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const;
};

class AsteroidSelectorSecondaryFilterModel : public QSortFilterProxyModel
{
public:
	AsteroidSelectorSecondaryFilterModel(QObject* parent, QAbstractItemModel* model);
protected:
	virtual bool filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const;
};

#endif // AsteroidSelectorFILTERPROXYMODEL_H
