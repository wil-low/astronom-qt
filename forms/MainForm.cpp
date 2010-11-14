#include "MainForm.h"
#include "ui_MainForm.h"

#include "InputForm.h"
#include "GlyphForm.h"

#include <QtGui>

#include "../utils/Ephemeris.h"
#include "../utils/TimeLoc.h"
#include "../utils/BodyProps.h"
#include "../utils/HouseProps.h"
#include "../utils/GlyphManager.h"
#include "../views/OcularView.h"
#include "../models/OcularDelegate.h"
#include "../widgets/PlanetSelector.h"

MainForm::MainForm(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainForm)
, input_(new InputForm)
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

	model_ = new QStandardItemModel(10, 2, this);

	QAbstractItemView* itemView = new OcularView(ui->centralwidget);
	view_ = itemView;
	ui->horizontalLayout->insertWidget(0, view_, 4);
	itemView->setModel(model_);

	connect(this, SIGNAL(reconfigure()), view_, SLOT(reconfigure()));
	PlanetSelector* planetSelector = new PlanetSelector(ui->centralwidget, model_);
	planetSelector->copySelectionModel(itemView);

	ui->horizontalLayout->insertWidget(1, planetSelector, 1);

	loadHouseMenu();
	timeLoc[0].data_[TL_DATETIME] = Ephemeris::now();
	timeLoc[0].data_[TL_LAT] = 45;
	timeLoc[0].data_[TL_LON] = 34;

	houseMenuTriggered(houseActionGroup_->checkedAction());
	emit reconfigure();

	ui->doubleSpinBox->setValue(1);
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
		setTimeLoc(0);
		emit reconfigure();
	}
}

void MainForm::on_actionGlyph_manager_activated()
{
	GlyphForm form;
	form.exec();
}

void MainForm::on_doubleSpinBox_valueChanged(double value)
{
	((OcularView*)view_)->recalcDimensionsByFactor(value);
}

void MainForm::setTimeLoc(int chart_index)
{
	const TimeLoc& tl = timeLoc[chart_index];
	model_->setHeaderData(chart_index, Qt::Horizontal, QVariant(&tl), Qt::UserRole);
	model_->removeRows(chart_index, model_->rowCount(QModelIndex()), QModelIndex());
	int bodies[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 17, 18};
	int row_count = 0;
	BodyProps props;
	for (int i = 0; i < sizeof(bodies) / sizeof(int); ++i) {
		model_->insertRows(row_count, 1, QModelIndex());
		Ephemeris::calc_body (props, bodies[i], 0, tl);
		props.id = bodies[i];
		props.type = TYPE_PLANET;
		model_->setData (model_->index(row_count, chart_index, QModelIndex()), qVariantFromValue(props));
		++row_count;
	}
	HouseProps houses;
	Ephemeris::calc_house(houses, tl);
	int cusp_count = tl.cuspCount();
//	addHouse(chart_index, HOUSE_ID_ASC, houses);
//	addHouse(chart_index, HOUSE_ID_MC, houses);
	for (int i = 0; i < tl.cuspCount(); ++i)
		addHouse(chart_index, HOUSE_ID_FIRST + i, houses, cusp_count);
}

void MainForm::addHouse (int chart_index, int id, const HouseProps& props, int cusp_count)
{
	int row = model_->rowCount();
	model_->insertRows(row, 1, QModelIndex());
	BodyProps hprops;
	hprops.id = id;
	hprops.type = TYPE_HOUSE;
	hprops.userData = cusp_count;
	hprops.prop[BodyProps::bp_Lon] = (id >= HOUSE_ID_FIRST) ?
									 props.cusps[id - HOUSE_ID_FIRST + 1] :
									 props.ascmc[id - HOUSE_ID_ASC];
	model_->setData (model_->index(row, chart_index, QModelIndex()), qVariantFromValue(hprops));
}

void MainForm::loadHouseMenu()
{
	GlyphManager::StringPairVector houses = GlyphManager::get_const_instance().houseMethod();
	ui->menuHouses->clear();
	for (int i = 0; i < houses.size(); ++i) {
		QAction* action = new QAction(tr(houses[i].second.toAscii()), this);
		action->setCheckable(true);
		action->setShortcut(QKeySequence(houses[i].first));
		houseActionGroup_->addAction(action);
		ui->menuHouses->addAction(action);
		if (i == 0)
			action->setChecked(true);
	}
}

void MainForm::houseMenuTriggered(QAction* action)
{
	if (action) {
		timeLoc[0].method_ = (const TimeLoc::house_method)action->shortcut().toString().toAscii().data()[0];
		setTimeLoc(0);
		view_->viewport()->update();
	}
}
