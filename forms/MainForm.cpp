#include "MainForm.h"
#include "ui_MainForm.h"

#include "InputForm.h"
#include "GlyphForm.h"

#include <QtGui>

#include "../utils/Ephemeris.h"
#include "../utils/TimeLoc.h"
#include "../utils/BodyProps.h"
#include "../utils/HouseProps.h"
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
	model_ = new QStandardItemModel(10, 2, this);

	QAbstractItemView* itemView = new OcularView(ui->centralwidget);
	view_ = itemView;
	ui->horizontalLayout->insertWidget(0, view_, 4);
	itemView->setModel(model_);

	view_->connect(this, SIGNAL(reconfigure()), SLOT(reconfigure()));
	PlanetSelector* planetSelector = new PlanetSelector(ui->centralwidget, model_);
	planetSelector->copySelectionModel(itemView);

	ui->horizontalLayout->insertWidget(1, planetSelector, 1);

	TimeLoc tl;
	tl.data_[TL_DATE] = Ephemeris::now();
	tl.data_[TL_LAT] = 45;
	tl.data_[TL_LON] = 34;
	setTimeLoc(0, tl);
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
//		scene_->update();
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

void MainForm::setTimeLoc(int chart_index, const TimeLoc & tl)
{
//	model_->setHeaderData(chart_index, Qt::Horizontal, QVariant(*tl), Qt::UserRole);
	model_->removeRows(chart_index, model_->rowCount(QModelIndex()), QModelIndex());
	int bodies[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 16, 17, 18};
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
	Ephemeris::calc_house(houses, HouseProps::hp_Placidus, tl);
	addHouse(chart_index, HOUSE_ID_ASC, houses);
	addHouse(chart_index, HOUSE_ID_MC, houses);
	for (int i = 0; i < houses.cuspCount(); ++i)
		addHouse(chart_index, HOUSE_ID_FIRST + i, houses);
}

void MainForm::addHouse (int chart_index, int id, const HouseProps& props)
{
	int row = model_->rowCount();
	model_->insertRows(row, 1, QModelIndex());
	BodyProps hprops;
	hprops.id = id;
	hprops.type = TYPE_HOUSE;
	hprops.userData = props.cuspCount();
	hprops.prop[BodyProps::bp_Lon] = (id >= HOUSE_ID_FIRST) ?
									 props.cusps[id - HOUSE_ID_FIRST + 1] :
									 props.ascmc[id - HOUSE_ID_ASC];
	model_->setData (model_->index(row, chart_index, QModelIndex()), qVariantFromValue(hprops));
}
