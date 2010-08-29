#include "MainForm.h"
#include "ui_MainForm.h"

#include "InputForm.h"
#include "GlyphForm.h"

#include <QtGui>

#include "../widgets/AstroLabel.h"
#include "../widgets/AspectLabel.h"
#include "../models/PlanetModel.h"
#include "../utils/Ephemeris.h"
#include "../views/OcularScene.h"

MainForm::MainForm(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainForm)
, input_(new InputForm)
{
	QFont font("Astronom");
	QFontInfo fi(font);
	QString fam = fi.family();
	ui->setupUi(this);
	model_ = new PlanetModel(3);
	TimeLoc tl;
	tl.data_[TL_DATE] = Ephemeris::now();
	model_->setTimeLoc(0, tl);
	ui->listView->setModel(model_);
	ui->listView->setModelColumn(0);
//	ui->graphicsView->setModel(model);

	scene_ = new OcularScene(this);

	scene_->connect(this, SIGNAL(reconfigure()), SLOT(reconfigure()));
	emit reconfigure();
	scene_->setModel(model_);

	ui->graphicsView->setScene(scene_);
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
		scene_->update();
	}
}

void MainForm::on_actionGlyph_manager_activated()
{
	GlyphForm form;
	form.exec();
}

void MainForm::on_doubleSpinBox_valueChanged(double value)
{
	QTransform transform;
	transform.scale(value, value);
	ui->graphicsView->setTransform(transform);
}
