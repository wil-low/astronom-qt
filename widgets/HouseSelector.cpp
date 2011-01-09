#include "HouseSelector.h"
#include "HouseSelectorDelegate.h"

#include "../models/HouseSelectorFilterProxyModel.h"
#include "../models/ModelHelper.h"

#include "../utils/constants.h"
#include "../utils/SettingsManager.h"
#include "../utils/TimeLoc.h"

#include <QVBoxLayout>
#include <QTabBar>
#include <QListView>
#include <QDebug>
#include <QApplication>
#include <QStandardItemModel>

HouseSelector::HouseSelector(QWidget *parent, QAbstractItemModel* model)
: BaseSelector(parent, model)
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	tabBar_ = new QTabBar(this);
	tabBar_->addTab(tr("Ecl."));
	tabBar_->setTabData(0, dm_Longitude);
	tabBar_->addTab(tr("Abs."));
	tabBar_->setTabData(1, dm_Absolute);
/*
	tabBar_->addTab(tr("R.A."));
	tabBar_->setTabData(2, dm_RectAsc);
	tabBar_->addTab(tr("Ob.A."));
	tabBar_->setTabData(3, dm_OblAsc);
	tabBar_->addTab(tr("L/D"));
	tabBar_->setTabData(4, dm_LatDecl);
*/
	connect(tabBar_, SIGNAL(currentChanged(int)), SLOT(tabChanged(int)));
	layout->addWidget(tabBar_);

	listMain_ = new QListView(this);
	listMain_->setEditTriggers(QListView::NoEditTriggers);
	listMain_->setUniformItemSizes(true);
	listMain_->setModel(new HouseSelectorMainFilterModel(this, model));
	connect(this, SIGNAL(invalidateViews()), listMain_->model(), SLOT(invalidate()));
	connect(listMain_, SIGNAL(pressed(const QModelIndex&)), SLOT(listMainPressed(const QModelIndex&)));
	layout->addWidget(listMain_);

	tabHouseMode_ = new QTabBar(this);
	SettingsManager::StringPairVector houses = SettingsManager::get_const_instance().houseMethodVec();
	for (int i = 0; i < houses.size(); ++i) {
		tabHouseMode_->addTab(houses[i].first);
		tabHouseMode_->setTabToolTip(i, houses[i].second.toAscii());
	}
	connect(tabHouseMode_, SIGNAL(currentChanged(int)), SLOT(houseModeChanged(int)));
	layout->addWidget(tabHouseMode_);

	alternateHouseModel_ = new QStandardItemModel(0, 1, this);

	listSecondary_ = new QListView(this);
	listSecondary_->setEditTriggers(QListView::NoEditTriggers);
	listSecondary_->setUniformItemSizes(true);
	listSecondary_->setModel(new HouseSelectorSecondaryFilterModel(this, alternateHouseModel_));
	connect(this, SIGNAL(invalidateViews()), listSecondary_->model(), SLOT(invalidate()));
	connect(listSecondary_, SIGNAL(pressed(const QModelIndex&)), SLOT(listSecondaryPressed(const QModelIndex&)));
	layout->addWidget(listSecondary_);

	tabChanged(tabBar_->currentIndex());
}

HouseSelector::~HouseSelector()
{
	delete tabHouseMode_;
	delete alternateHouseModel_;
}

void HouseSelector::setDelegate(QListView* listView, int fontSize, int property)
{
	QAbstractItemDelegate* old = listView->itemDelegate();
	listView->setFont(*SettingsManager::get_const_instance().font(fontSize, FF_ASTRO));
	listView->setItemDelegate(new HouseSelectorDelegate(this, property, fontSize));
	delete old;
}

void HouseSelector::houseModeChanged(int index)
{
	TimeLoc tl = qVariantValue<TimeLoc>(model_->headerData(0, Qt::Horizontal, Qt::UserRole));
	tl.method_ = tabHouseMode_->tabText(index);
	alternateHouseModel_->setHeaderData(0, Qt::Horizontal, qVariantFromValue(tl), Qt::UserRole);
	ModelHelper modelHelper(tl, alternateHouseModel_, 0, true);
	modelHelper.insertHouses();
	emit invalidateViews();
}

void HouseSelector::timeloc_changed()
{
	TimeLoc tl = qVariantValue<TimeLoc>(model_->headerData(0, Qt::Horizontal, Qt::UserRole));
	const SettingsManager::StringPairVector& houses = SettingsManager::get_const_instance().houseMethodVec();
	QString houseModeStr;
	QString hm;
	for (int i = 0; i < houses.size(); ++i) {
		hm = houses[i].first;
		if (hm == tl.method_) {
			houseModeStr = houses[i].first;
			tabBar_->setTabText(0, tr(houses[i].second.toAscii().data()));
			tabBar_->setTabToolTip(0, houseModeStr);
			break;
		}
		hm.clear();
	}
	houseModeChanged (tabHouseMode_->currentIndex());
}
