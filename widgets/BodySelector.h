#ifndef BODYSELECTOR_H
#define BODYSELECTOR_H

#include "BaseSelector.h"

class QSortFilterProxyModel;

class BodySelector : public BaseSelector
{
    Q_OBJECT
public:
	explicit BodySelector(QWidget *parent, QAbstractItemModel* model);
public slots:

protected:
	virtual BaseSelectorDelegate* getDelegate();
};

#endif // BODYSELECTOR_H
