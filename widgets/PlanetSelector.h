#ifndef PLANETSELECTOR_H
#define PLANETSELECTOR_H

#include "BaseSelector.h"

class PlanetSelector : public BaseSelector
{
    Q_OBJECT
public:
	explicit PlanetSelector(QWidget *parent, QAbstractItemModel* model);

public slots:

protected:
	virtual void setDelegate(QListView* listView, int fontSize, int property);
};

#endif // PLANETSELECTOR_H
