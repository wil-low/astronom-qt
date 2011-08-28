#include "MainForm.h"
#include "ui_MainForm.h"

#include "InputForm.h"
#include "GlyphForm.h"
#include "FormulaForm.h"
#include "PersonsForm.h"
#include "ImportForm.h"

#include "../models/OcularDelegate.h"

#include "../utils/BodyProps.h"
#include "../utils/Ephemeris.h"
#include "../utils/TimeLoc.h"
#include "../utils/SettingsManager.h"
#include "../utils/DocumentManager.h"

#include "../widgets/DocumentWidget.h"
#include "../views/OcularView.h"
#include "../views/SpeculumView.h"

#include "../widgets/PlanetSelector.h"
#include "../widgets/HouseSelector.h"
#include "../widgets/AsteroidSelector.h"

#include "../labels/AstroLabel.h"

#include <QtGui>

const doc_mode_t DOC_MODE_ON_START = doc_Ocular;

MainForm::MainForm(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainForm)
, input_(new InputForm(this))
, persons_(new PersonsForm(this))
, manager_(new DocumentManager(this))
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

	ui->setupUi(this);
	houseActionGroup_ = new QActionGroup(this);
	assert (connect(houseActionGroup_, SIGNAL(triggered(QAction*)), manager_, SLOT(houseMenuTriggered(QAction*))) &&
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

	ui->centralwidget->insertTab(0, new DocumentWidget(this, doc_Ocular), QIcon(), "Ocular");
	ui->centralwidget->insertTab(1, new DocumentWidget(this, doc_Speculum), QIcon(), "Speculum");
	ui->centralwidget->insertTab(2, new QPushButton("H3", this), QIcon(), "Hello3");
	ui->centralwidget->insertTab(3, new QPushButton("H4", this), QIcon(), "Hello4");
	ui->centralwidget->setTabEnabled(0, true);
	ui->centralwidget->setTabEnabled(1, true);
	connect(ui->centralwidget, SIGNAL(currentAboutToShow(int)), manager_, SLOT(centralViewAboutToChange(int)));
	manager_->changeMode(DOC_MODE_ON_START);
	manager_->changeHouseMethod("P");
}

MainForm::~MainForm()
{
	delete input_;
	delete persons_;
	delete manager_;
	delete ui;
}

void MainForm::on_actionInput_data_activated()
{
	if (input_->exec() == QDialog::Accepted)
		applyInputData();
}

void MainForm::applyInputData()
{
	/*
	timeLoc[0] = input_->toTimeLoc();
	qDebug() << __FUNCTION__ << timeLoc[0];
	setWindowTitle(input_->titleStr() + " - Astronom");
	timeLoc[0].method_ = SettingsManager::get_const_instance().houseMethod();
	manager_->setTimeLoc(0);
	emit reconfigure();
	updateViews();
	*/
}

void MainForm::on_actionGlyph_manager_activated()
{
	GlyphForm form;
	form.exec();
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
/*
void MainForm::updateViews()
{
	emit updateCentralView();
}
*/
void MainForm::on_actionFormula_activated()
{
	/*
	FormulaForm form(this);
	ModelHelper modelHelper(timeLoc[0], model_, 0, false);
	BodyProps bp;
	int index = 0;
	while (modelHelper.propsByIndex(index++, 0, &bp)) {
		form.setVariable(SettingsManager::get_const_instance().formulaVariable(bp),
			bp.prop[BodyProps::bp_Lon]);
	}
	form.exec();*/
}

void MainForm::on_actionPersons_activated()
{
	persons_->show();
}
/*
void MainForm::timeloc_set(const TimeLoc& tl)
{
	input_->fromTimeLoc(tl);
	applyInputData();
}
*/
void MainForm::createDockWindows()
{
/*
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

	dock = new QDockWidget(tr("Bottom dock"), this);
	dock->setAllowedAreas(Qt::BottomDockWidgetArea);
	addDockWidget(Qt::BottomDockWidgetArea, dock);

	setUnifiedTitleAndToolBarOnMac(true);
	*/
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
//	assert (connect(centralViewActionGroup_, SIGNAL(triggered(QAction*)), manager_, SLOT(centralViewMenuTriggered(QAction*))) &&
//			"centralViewMenu connect failed");
	for (int i = 0; i < sizeof(CENTRAL_VIEW_CAPTIONS) / sizeof(CENTRAL_VIEW_CAPTIONS[0]); ++i) {
		QAction* action = new QAction(tr(CENTRAL_VIEW_CAPTIONS[i]), this);
		action->setCheckable(true);
		action->setData(i);
		centralViewActionGroup_->addAction(action);
		ui->menuView->addAction(action);
		if (i == DOC_MODE_ON_START)
			action->setChecked(true);
	}

	ui->menuView->addSeparator();
}
/*
void MainForm::centralViewMenuTriggered(QAction* action)
{
	if (action) {
		central_view_t type = static_cast<central_view_t>(action->data().toInt());
		manager_->changeCentralView(type);
	}
}
*/
