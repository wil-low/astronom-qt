#ifndef PLANETSELECTOR_H
#define PLANETSELECTOR_H

#include "BodySelector.h"

class PlanetSelector : public BodySelector
{
    Q_OBJECT
public:
	explicit PlanetSelector(QWidget *parent, QAbstractItemModel* model);

public slots:

protected:
	virtual QSortFilterProxyModel* getFilterModel(model_t modelType);
};

#endif // PLANETSELECTOR_H
