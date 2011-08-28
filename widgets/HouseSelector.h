#ifndef HouseSelector_H
#define HouseSelector_H

#include "BaseSelector.h"

class HouseSelector : public BaseSelector
{
    Q_OBJECT
public:
	explicit HouseSelector(QWidget *parent, QAbstractItemModel* model);
	~HouseSelector();
signals:

public slots:
	void houseModeChanged(int index);
	virtual void timeloc_changed();

protected:
	virtual BaseSelectorDelegate* getDelegate();
	virtual QSortFilterProxyModel* getFilterModel(model_t modelType);

private:
	QTabBar* tabHouseMode_;
	QAbstractItemModel* alternateHouseModel_;
};

#endif // HouseSelector_H
