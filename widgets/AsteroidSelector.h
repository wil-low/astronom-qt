#ifndef AsteroidSelector_H
#define AsteroidSelector_H

#include "BodySelector.h"

class AsteroidSelector : public BodySelector
{
    Q_OBJECT
public:
	explicit AsteroidSelector(QWidget *parent, QAbstractItemModel* model);

public slots:

protected:
	virtual QSortFilterProxyModel* getFilterModel(model_t modelType);
};

#endif // AsteroidSelector_H
