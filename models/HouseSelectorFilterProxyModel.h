#ifndef HouseSelectorFILTERPROXYMODEL_H
#define HouseSelectorFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class HouseSelectorMainFilterModel : public QSortFilterProxyModel
{
public:
	HouseSelectorMainFilterModel(QObject* parent, QAbstractItemModel* model);
protected:
	virtual bool filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const;
};

class HouseSelectorSecondaryFilterModel : public QSortFilterProxyModel
{
public:
	HouseSelectorSecondaryFilterModel(QObject* parent, QAbstractItemModel* model);
protected:
	virtual bool filterAcceptsRow (int sourceRow, const QModelIndex & sourceParent) const;
};

#endif // HouseSelectorFILTERPROXYMODEL_H
