#include "PlanetSelector.h"
#include <QFont>

PlanetSelector::PlanetSelector(QWidget *parent) :
    QListView(parent)
{
	setEditTriggers(QAbstractItemView::NoEditTriggers);
}
