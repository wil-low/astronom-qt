#include "MainForm.h"
#include "ui_MainForm.h"

#include "InputForm.h"
#include "GlyphForm.h"
#include "FormulaForm.h"
#include "PersonsForm.h"
#include "ImportForm.h"

#include "../models/ModelHelper.h"
#include "../models/OcularDelegate.h"

#include "../utils/BodyProps.h"
#include "../utils/Ephemeris.h"
#include "../utils/TimeLoc.h"
#include "../utils/SettingsManager.h"

#include "../views/OcularView.h"
#include "../views/SpeculumView.h"

#include "../widgets/PlanetSelector.h"
#include "../widgets/HouseSelector.h"
#include "../widgets/AsteroidSelector.h"

#include <QtGui>

const central_view_t CENTRAL_VIEW_ON_START = cv_Speculum;//cv_Wheel;

MainForm::MainForm(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainForm)
, input_(new InputForm(this))
, persons_(new PersonsForm(this))
, view_(NULL)
{
	//setAttribute(Qt::WA_DeleteOnClose);
#ifdef __linux
	Ephemeris::init("/home/willow/prj/ephem");
#else
	Ephemeris::init("d:/prj/amax-hg/Astromaximum/swiss");
#endif
	QFont font("Astronom");
	QFontInfo fi(font);
	QString fam = fi.family();

	model_ = new QStandardItemModel(0, 2, this);

	ui->setupUi(this);
	houseActionGroup_ = new QActionGroup(this);
	assert (connect(houseActionGroup_, SIGNAL(triggered(QAction*)), this, SLOT(houseMenuTriggered(QAction*))) &&
			"houseMenu connect failed");
	loadCentralViewMenu();
/*
	OcularView* itemView = new OcularView(ui->centralwidget);
	connect(this, SIGNAL(updateCentralView()), itemView, SLOT(invalidateView()));

	view_ = itemView;
	ui->horizontalLayout->insertWidget(0, view_, 4);
	itemView->setModel(model_);

	connect(this, SIGNAL(reconfigure()), view_, SLOT(reconfigure()));
*/
	loadHouseMenu();

	createDockWindows();

	connect(persons_, SIGNAL(timeloc_set(const TimeLoc&)), this, SLOT(timeloc_set(const TimeLoc&)));

	changeCentralView(CENTRAL_VIEW_ON_START);
	changeHouseMethod("P");
}

MainForm::~MainForm()
{
	delete model_;
	delete input_;
	delete persons_;
	delete ui;
}

void MainForm::on_actionInput_data_activated()
{
	if (input_->exec() == QDialog::Accepted)
		applyInputData();
}

void MainForm::applyInputData()
{
	timeLoc[0] = input_->toTimeLoc();
	qDebug() << __FUNCTION__ << timeLoc[0];
	setWindowTitle(input_->titleStr() + " - Astronom");
	timeLoc[0].method_ = SettingsManager::get_const_instance().houseMethod();
	setTimeLoc(0);
	emit reconfigure();
//	((OcularView*)view_)->recalcDimensionsByFactor(1);
}

void MainForm::on_actionGlyph_manager_activated()
{
	GlyphForm form;
	form.exec();
}

void MainForm::setTimeLoc(int chart_index)
{
	const TimeLoc& tl = timeLoc[chart_index];
	model_->setHeaderData(chart_index, Qt::Horizontal, qVariantFromValue(tl), Qt::UserRole);

	ModelHelper modelHelper(tl, model_, chart_index, true);
	int bodies[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 17, 18};
	for (int i = 0; i < sizeof(bodies) / sizeof(int); ++i) {
		modelHelper.insertPlanet(bodies[i], true);
	}
	modelHelper.insertHouses();

	emit timeloc_changed();
}

void MainForm::loadHouseMenu()
{
	ui->menuHouses->clear();
	const SettingsManager::StringPairVector& houses = SettingsManager::get_const_instance().houseMethodVec();
	QString hm = SettingsManager::get_const_instance().houseMethod();
	for (int i = 0; i < houses.size(); ++i) {
		QAction* action = new QAction(tr(houses[i].second.toAscii()), this);
		action->setCheckable(true);
		action->setShortcut(QKeySequence(houses[i].first));
		action->setData(houses[i].first);
		houseActionGroup_->addAction(action);
		ui->menuHouses->addAction(action);
		if (hm == houses[i].first)
			action->setChecked(true);
	}
}

void MainForm::houseMenuTriggered(QAction* action)
{
	if (action) {
		changeHouseMethod(action->data().toString());
		view_->viewport()->update();
	}
}

void MainForm::changeHouseMethod(const QString& method)
{
	SettingsManager::get_mutable_instance().setHouseMethod(method);
	timeLoc[0].method_ = SettingsManager::get_const_instance().houseMethod();
	setTimeLoc(0);
}

void MainForm::updateViews()
{
	emit updateCentralView();
}

void MainForm::on_actionFormula_activated()
{
	FormulaForm form(this);
	ModelHelper modelHelper(timeLoc[0], model_, 0, false);
	BodyProps bp;
	int index = 0;
	while (modelHelper.propsByIndex(index++, 0, &bp)) {
		form.setVariable(SettingsManager::get_const_instance().formulaVariable(bp.type, bp.id),
			bp.prop[BodyProps::bp_Lon]);
	}
	form.exec();
}

void MainForm::on_actionPersons_activated()
{
	persons_->show();
}

void MainForm::timeloc_set(const TimeLoc& tl)
{
	input_->fromTimeLoc(tl);
	applyInputData();
}

void MainForm::createDockWindows()
{
	QDockWidget *dock = new QDockWidget(tr("Data dock"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	QTabWidget* tabBodyList = new QTabWidget(dock);

	PlanetSelector* planetSelector = new PlanetSelector(this, model_);
	planetSelector->setFilterModels();
	//	planetSelector->copySelectionModel(itemView);
	connect(this, SIGNAL(timeloc_changed()), planetSelector, SLOT(timeloc_changed()));
	connect(planetSelector, SIGNAL(invalidateViews()), this, SLOT(updateViews()));
	tabBodyList->addTab(planetSelector, tr("Planets"));

	HouseSelector* houseSelector = new HouseSelector(this, model_);
	houseSelector->setFilterModels();
	//	houseSelector->copySelectionModel(itemView);
	connect(this, SIGNAL(timeloc_changed()), houseSelector, SLOT(timeloc_changed()));
	tabBodyList->addTab(houseSelector, tr("Houses"));

	AsteroidSelector* asteroidSelector = new AsteroidSelector(this, model_);
	asteroidSelector->setFilterModels();
	//	AsteroidSelector->copySelectionModel(itemView);
	connect(this, SIGNAL(timeloc_changed()), asteroidSelector, SLOT(timeloc_changed()));
	tabBodyList->addTab(asteroidSelector, tr("Asteroids"));

	dock->setWidget(tabBodyList);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	ui->menuView->addAction(dock->toggleViewAction());
	setUnifiedTitleAndToolBarOnMac(true);
}

void MainForm::on_actionImport_triggered()
{
	ImportForm import(this);
	import.exec();
}

void MainForm::loadCentralViewMenu()
{
	static const char* CENTRAL_VIEW_CAPTIONS[] = {
		"Wheel", // cv_Wheel
		"Speculum", // cv_Speculum
	};

	ui->menuView->addSeparator(); //->setText(tr("CentralView"));

	centralViewActionGroup_ = new QActionGroup(this);
	assert (connect(centralViewActionGroup_, SIGNAL(triggered(QAction*)), this, SLOT(centralViewMenuTriggered(QAction*))) &&
			"centralViewMenu connect failed");
	for (int i = 0; i < sizeof(CENTRAL_VIEW_CAPTIONS) / sizeof(CENTRAL_VIEW_CAPTIONS[0]); ++i) {
		QAction* action = new QAction(tr(CENTRAL_VIEW_CAPTIONS[i]), this);
		action->setCheckable(true);
		action->setData(i);
		centralViewActionGroup_->addAction(action);
		ui->menuView->addAction(action);
		if (i == CENTRAL_VIEW_ON_START)
			action->setChecked(true);
	}

	ui->menuView->addSeparator();
}

void MainForm::centralViewMenuTriggered(QAction* action)
{
	if (action) {
		central_view_t type = static_cast<central_view_t>(action->data().toInt());
		changeCentralView(type);
	}
}

void MainForm::changeCentralView(central_view_t type)
{
	delete view_;
	view_ = NULL;
	switch (type) {
	case cv_Wheel: {
		OcularView* itemView = new OcularView(ui->centralwidget);
		connect(this, SIGNAL(updateCentralView()), itemView, SLOT(invalidateView()));
		view_ = itemView;
		break; }
	case cv_Speculum:
		SpeculumView* speculumView = new SpeculumView(ui->centralwidget);
		view_ = speculumView;
		break;
	}
	if (view_) {
		qDebug() << __FUNCTION__ << type;
		ui->horizontalLayout->insertWidget(0, view_, 4);
		connect(this, SIGNAL(reconfigure()), view_, SLOT(reconfigure()));
		view_->setModel(model_);
		applyInputData();
		emit reconfigure();
	}
}
