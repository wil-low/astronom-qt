#include "MainForm.h"
#include "ui_MainForm.h"

#include "InputForm.h"
#include "GlyphForm.h"
#include "FormulaForm.h"

#include "../models/ModelHelper.h"
#include "../models/OcularDelegate.h"

#include "../utils/BodyProps.h"
#include "../utils/Ephemeris.h"
#include "../utils/TimeLoc.h"
#include "../utils/SettingsManager.h"

#include "../views/OcularView.h"

#include "../widgets/PlanetSelector.h"
#include "../widgets/HouseSelector.h"
#include "../widgets/AsteroidSelector.h"

#include <QtGui>

MainForm::MainForm(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainForm)
, input_(new InputForm(this))
{
#ifdef __linux
	Ephemeris::init("/home/willow/prj/ephem");
#else
	Ephemeris::init("d:/prj/amax-hg/Astromaximum/swiss");
#endif
	QFont font("Astronom");
	QFontInfo fi(font);
	QString fam = fi.family();

	ui->setupUi(this);
	houseActionGroup_ = new QActionGroup(this);
	assert (connect(houseActionGroup_, SIGNAL(triggered(QAction*)), this, SLOT(houseMenuTriggered(QAction*))) &&
			"houseMenu connect failed");

	model_ = new QStandardItemModel(0, 2, this);

	OcularView* itemView = new OcularView(ui->centralwidget);
	connect(this, SIGNAL(updateCentralView()), itemView, SLOT(invalidateView()));

	view_ = itemView;
	ui->horizontalLayout->insertWidget(0, view_, 4);
	itemView->setModel(model_);

	connect(this, SIGNAL(reconfigure()), view_, SLOT(reconfigure()));

	loadHouseMenu();
	timeLoc[0].data_[TL_DATETIME] = Ephemeris::now();
	timeLoc[0].data_[TL_LAT] = 45;
	timeLoc[0].data_[TL_LON] = 34;

	QTabWidget* tabBodyList = new QTabWidget(ui->centralwidget);

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

	ui->horizontalLayout->insertWidget(1, tabBodyList, 1);

	houseMenuTriggered(houseActionGroup_->checkedAction());
	emit reconfigure();
	((OcularView*)view_)->recalcDimensionsByFactor(1);
/*
	AstroLabel* text = new AstroLabel("Hello");
//	scene_->addItem(text);
	text->setPos(300, 300);
	AspectLabel* asp = new AspectLabel;
	scene_->addItem(asp);
	view_ = new QGraphicsView(scene_);
	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(view_);
		ui->centralwidget->setLayout(layout);*/
}

MainForm::~MainForm()
{
	delete model_;
	delete input_;
    delete ui;
}

void MainForm::on_actionInput_data_activated()
{
	if (input_->exec() == QDialog::Accepted) {
		timeLoc[0] = input_->toTimeLoc();
		timeLoc[0].method_ = SettingsManager::get_const_instance().houseMethod();
		setTimeLoc(0);
		emit reconfigure();
		((OcularView*)view_)->recalcDimensionsByFactor(1);
	}
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
		SettingsManager::get_mutable_instance().setHouseMethod(action->data().toString());
		timeLoc[0].method_ = SettingsManager::get_const_instance().houseMethod();
		setTimeLoc(0);
		view_->viewport()->update();
	}
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
