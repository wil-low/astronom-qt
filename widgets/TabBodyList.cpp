#include "TabBodyList.h"
#include <QStandardItemModel>

#include "../widgets/PlanetSelector.h"
#include "../widgets/HouseSelector.h"
#include "../widgets/AsteroidSelector.h"

TabBodyList::TabBodyList(QWidget *parent, QObject* sender)
: QTabWidget(parent)
{
	model_ = new QStandardItemModel(0, 2, this);
	PlanetSelector* planetSelector = new PlanetSelector(this, model_);
	planetSelector->setFilterModels();
	//	planetSelector->copySelectionModel(itemView);
	connect(sender, SIGNAL(timeloc_changed()), planetSelector, SLOT(timeloc_changed()));
//	connect(planetSelector, SIGNAL(invalidateViews()), sender, SLOT(updateViews()));
	addTab(planetSelector, tr("Planets"));

	HouseSelector* houseSelector = new HouseSelector(this, model_);
	houseSelector->setFilterModels();
	//	houseSelector->copySelectionModel(itemView);
	connect(sender, SIGNAL(timeloc_changed()), houseSelector, SLOT(timeloc_changed()));
	addTab(houseSelector, tr("Houses"));

	AsteroidSelector* asteroidSelector = new AsteroidSelector(this, model_);
	asteroidSelector->setFilterModels();
	//	AsteroidSelector->copySelectionModel(itemView);
	connect(sender, SIGNAL(timeloc_changed()), asteroidSelector, SLOT(timeloc_changed()));
	addTab(asteroidSelector, tr("Asteroids"));
}

void TabBodyList::insertPlanet()
{
}

void TabBodyList::insertHouse()
{
}
