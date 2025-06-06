#include "DocumentManager.h"

#include "../models/ModelHelper.h"
#include "../models/AspectModelHelper.h"

#include "../widgets/QtCreator/fancytabwidget.h"
#include "../widgets/DocumentWidget.h"

#include "../forms/FormulaForm.h"

#include "BodyProps.h"
#include "SettingsManager.h"

#include <boost/foreach.hpp>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QAction>
#include <QWidget>
#include <QSettings>

const char* TAB_CAPTIONS[] = {
	"Ocular",
	"Speculum"
};

int docType2tabIndex(doc_mode_t type)
{
	switch (type) {
	case doc_Ocular:
		return 0;
	case doc_Speculum:
		return 1;
	}
	return -1;
}

DocumentManager::DocumentManager(QWidget *parent)
: parent_(parent)
, bodyModel_(new QStandardItemModel(0, 2, this))
, aspectModel_(new QStandardItemModel(0, 1, this))
{
	documents_.resize(doc_Last);
}

DocumentManager::~DocumentManager()
{
	if (tabWidget_)
		saveState();
	delete bodyModel_;
}

void DocumentManager::setTimeLoc(int chart_index, const TimeLoc& tl)
{
	timeLoc[chart_index] = tl;
    bodyModel_->setHeaderData(chart_index, Qt::Horizontal, QVariant::fromValue(tl), Qt::UserRole);

	ModelHelper modelHelper(timeLoc[chart_index], bodyModel_, chart_index, true);
	int bodies[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 17, 18};
	for (int i = 0; i < sizeof(bodies) / sizeof(int); ++i) {
		modelHelper.insertPlanet(bodies[i], true);
	}
	modelHelper.insertHouses();

	AspectModelHelper aspectModelHelper(aspectModel_, true);
	aspectModelHelper.insertAspects(bodyModel_, chart_index, chart_index);

	emit timeloc_changed();
	emit reconfigure();
	//statusBar()->showMessage(AstroLabel::statistics());
}


void DocumentManager::setMode(doc_mode_t type)
{
	emit setCurrentTab(docType2tabIndex(type));
}

void DocumentManager::currentAboutToShow(int index)
{

//	QMessageBox::information(parent_, "", QString::number(index));
}

void DocumentManager::houseMenuTriggered(QAction* action)
{
	if (action) {
		changeHouseMethod(action->data().toString());
		//view_->viewport()->update();
	}
}

void DocumentManager::changeHouseMethod(const QString& method)
{
	SettingsManager::get_mutable_instance().setHouseMethod(method);
	timeLoc[0].method_ = SettingsManager::get_const_instance().houseMethod();
	setTimeLoc(0, timeLoc[0]);
}

void DocumentManager::setControlledWidget(Core::Internal::FancyTabWidget* w)
{
	tabWidget_ = w;
	for (int dt = doc_Ocular; dt < doc_Last; ++dt) {
		int tabIndex = docType2tabIndex((doc_mode_t)dt);
		if (tabIndex != -1) {
			DocumentWidget* docWidget = new DocumentWidget(this, (doc_mode_t)dt, bodyModel_, aspectModel_);
			docWidget->setObjectName(TAB_CAPTIONS[tabIndex]);
			connect(this, SIGNAL(reconfigure()), docWidget, SLOT(reconfigure()));
			tabWidget_->insertTab(tabIndex, docWidget, QIcon(), tr(TAB_CAPTIONS[tabIndex]));
			tabWidget_->setTabEnabled(tabIndex, true);
			documents_[dt] = docWidget;
		}
	}
	connect(this, SIGNAL(setCurrentTab(int)), tabWidget_, SLOT(setCurrentIndex(int)));
	connect(tabWidget_, SIGNAL(currentAboutToShow(int)), this, SLOT(currentAboutToShow(int)));
	restoreState();
}

void DocumentManager::saveState()
{
	QSettings settings;
	settings.beginGroup("DocumentWidget");
	BOOST_FOREACH(DocumentWidget* dw, documents_)
		dw->saveState(settings);
	settings.endGroup();
}

void DocumentManager::restoreState()
{
	QSettings settings;
	settings.beginGroup("DocumentWidget");
	BOOST_FOREACH(DocumentWidget* dw, documents_)
		dw->restoreState(settings);
	settings.endGroup();
}

void DocumentManager::setVariables(FormulaForm& form)
{
	ModelHelper modelHelper(timeLoc[0], bodyModel_, 0, false);
	BodyProps bp;
	int index = 0;
	while (modelHelper.propsByIndex(index++, 0, &bp)) {
		form.setVariable(SettingsManager::get_const_instance().formulaVariable(bp),
			bp.prop[BodyProps::bp_Lon]);
	}
}
