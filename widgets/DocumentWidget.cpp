#include "DocumentWidget.h"

#include "../views/OcularView.h"
#include "../views/SpeculumView.h"

#include "../widgets/PlanetSelector.h"
#include "../widgets/HouseSelector.h"
#include "../widgets/AsteroidSelector.h"

#include <QVBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QSettings>

DocumentWidget::DocumentWidget(const QObject* manager, doc_mode_t viewType, QAbstractItemModel* model)
: viewType_(viewType)
, view_(NULL)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	vertSplitter_ = new QSplitter(Qt::Vertical, this);
	layout->addWidget(vertSplitter_);

//	QVBoxLayout* layout = new QVBoxLayout(this);

	horizSplitter_ = new QSplitter(this);
	vertSplitter_->addWidget(horizSplitter_);
	vertSplitter_->addWidget(new QLabel("Hello"));

	switch (viewType_) {
	case doc_Ocular: {
		OcularView* itemView = new OcularView(this);
		//connect(manager, SIGNAL(updateCentralView()), itemView, SLOT(invalidateView()));
		view_ = itemView;
		break; }
	case doc_Speculum:
		SpeculumView* speculumView = new SpeculumView(this);
		view_ = speculumView;
		break;
	}
	if (view_) {
		horizSplitter_->addWidget(view_);
		view_->setModel(model);

		QTabWidget* tabBodyList = new QTabWidget(this);

		PlanetSelector* planetSelector = new PlanetSelector(this, model);
		planetSelector->setFilterModels();
		//	planetSelector->copySelectionModel(itemView);
		connect(manager, SIGNAL(timeloc_changed()), planetSelector, SLOT(timeloc_changed()));
		//connect(planetSelector, SIGNAL(invalidateViews()), this, SLOT(updateViews()));
		tabBodyList->addTab(planetSelector, tr("Planets"));

		HouseSelector* houseSelector = new HouseSelector(this, model);
		houseSelector->setFilterModels();
		//	houseSelector->copySelectionModel(itemView);
		connect(manager, SIGNAL(timeloc_changed()), houseSelector, SLOT(timeloc_changed()));
		tabBodyList->addTab(houseSelector, tr("Houses"));

		AsteroidSelector* asteroidSelector = new AsteroidSelector(this, model);
		asteroidSelector->setFilterModels();
		//	AsteroidSelector->copySelectionModel(itemView);
		connect(manager, SIGNAL(timeloc_changed()), asteroidSelector, SLOT(timeloc_changed()));
		tabBodyList->addTab(asteroidSelector, tr("Asteroids"));

		horizSplitter_->addWidget(tabBodyList);
	}
}

void DocumentWidget::reconfigure()
{
	view_->reconfigure();
}

void DocumentWidget::saveState(QSettings& settings)
{
	settings.beginGroup(objectName());
	settings.setValue("vertSplitter", vertSplitter_->saveState());
	settings.setValue("horizSplitter", horizSplitter_->saveState());
	settings.beginGroup("centralView");
	view_->saveState(settings);
	settings.endGroup();
	settings.endGroup();
}

void DocumentWidget::restoreState(QSettings& settings)
{
	settings.beginGroup(objectName());
	vertSplitter_->restoreState(settings.value("vertSplitter").toByteArray());
	horizSplitter_->restoreState(settings.value("horizSplitter").toByteArray());
	settings.beginGroup("centralView");
	view_->restoreState(settings);
	settings.endGroup();
	settings.endGroup();
}
