#include "MainForm.h"
#include "ui_MainForm.h"

#include "InputForm.h"
#include "GlyphForm.h"
#include "FormulaForm.h"
#include "PersonsForm.h"
#include "ImportForm.h"

#include "../utils/BodyProps.h"
#include "../utils/Ephemeris.h"
#include "../utils/TimeLoc.h"
#include "../utils/SettingsManager.h"
#include "../utils/DocumentManager.h"

#include "../labels/AstroLabel.h"

#include <QtGui>

const doc_mode_t DOC_MODE_ON_START = doc_Ocular;
//const doc_mode_t DOC_MODE_ON_START = doc_Speculum;

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
	loadHouseMenu();

	connect(persons_, SIGNAL(timeloc_set(const TimeLoc&)), this, SLOT(timeloc_set(const TimeLoc&)));
	//connect(this, SIGNAL(reconfigure()), manager_, SLOT(reconfigure()));
	manager_->setControlledWidget(ui->centralwidget);
	manager_->changeHouseMethod("P");
	manager_->setMode(DOC_MODE_ON_START);
	applyInputData();
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
	TimeLoc timeLoc = input_->toTimeLoc();
	qDebug() << __FUNCTION__ << timeLoc;
	setWindowTitle(input_->titleStr() + " - Astronom");
	timeLoc.method_ = SettingsManager::get_const_instance().houseMethod();
	manager_->setTimeLoc(0, timeLoc);
	//emit reconfigure();
//	emit updateDocument();
//	updateViews();
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
        QAction* action = new QAction(tr(houses[i].second.toLatin1()), this);
		action->setCheckable(true);
		action->setShortcut(QKeySequence(houses[i].first));
		action->setData(houses[i].first);
		houseActionGroup_->addAction(action);
		ui->menuHouses->addAction(action);
		if (hm == houses[i].first)
			action->setChecked(true);
	}
}

void MainForm::on_actionFormula_activated()
{
	FormulaForm form(this);
	manager_->setVariables(form);
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

void MainForm::on_actionImport_triggered()
{
	ImportForm import(this);
	import.exec();
}
/*
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

void MainForm::centralViewMenuTriggered(QAction* action)
{
	if (action) {
		central_view_t type = static_cast<central_view_t>(action->data().toInt());
		manager_->changeCentralView(type);
	}
}
*/
