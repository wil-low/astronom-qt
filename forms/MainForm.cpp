#include "MainForm.h"
#include "ui_MainForm.h"

#include "InputForm.h"
#include "GlyphForm.h"

#include <QtGui>

#include "../widgets/AstroLabel.h"
#include "../widgets/AspectLabel.h"
#include "../models/PlanetModel.h"
#include "../utils/Ephemeris.h"

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
	QFont font("Astronom");
	QFontInfo fi(font);
	QString fam = fi.family();
	ui->setupUi(this);
	PlanetModel* model = new PlanetModel(3);
	TimeLoc tl;
	tl.data_[TL_DATE] = Ephemeris::now();
	model->setTimeLoc(0, tl);
	ui->tableView->setModel(model);
	ui->listView->setModel(model);
	ui->listView->setModelColumn(0);
//	ui->graphicsView->setModel(model);
	/*
	scene_ = new QGraphicsScene(this);
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
    delete ui;
}

void MainForm::on_actionInput_data_activated()
{
	InputForm input;
	input.exec();
}

void MainForm::on_actionGlyph_manager_activated()
{
	GlyphForm form;
	form.exec();
}
