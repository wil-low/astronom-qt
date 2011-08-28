#include "DocumentManager.h"
#include "../models/ModelHelper.h"
#include "SettingsManager.h"

#include <QStandardItemModel>
#include <QMessageBox>
#include <QAction>
#include <QWidget>

DocumentManager::DocumentManager(QWidget *parent)
: parent_(parent)
{
	model_ = new QStandardItemModel(0, 2, this);
}

DocumentManager::~DocumentManager()
{
//	if (view_)
//		view_->saveSettings();
	delete model_;
}

void DocumentManager::setTimeLoc(int chart_index)
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
	//statusBar()->showMessage(AstroLabel::statistics());
}

void DocumentManager::changeMode(doc_mode_t type)
{
/*
	CentralView* old_view = view_;
	if (old_view)
		old_view->saveSettings();
	view_ = NULL;
	switch (type) {
	case cv_Ocular: {
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
		ui->horizontalLayout->insertWidget(1, view_, 4);
		connect(this, SIGNAL(reconfigure()), view_, SLOT(reconfigure()));
		view_->setModel(model_);
		applyInputData();
		emit reconfigure();
	}
	delete old_view;*/
}

void DocumentManager::centralViewAboutToChange(int index)
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
	setTimeLoc(0);
}

