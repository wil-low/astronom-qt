#include "PlanetSelector.h"
#include "PlanetSelectorDelegate.h"
#include "../models/PlanetSelectorFilterProxyModel.h"
#include "utils/constants.h"
#include "../utils/GlyphManager.h"
#include <QVBoxLayout>
#include <QTabBar>
#include <QListView>
#include <QDebug>
#include <QApplication>

PlanetSelector::PlanetSelector(QWidget *parent, QAbstractItemModel* model)
: BaseSelector(parent, model)
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	tabBar_ = new QTabBar(this);
	tabBar_->addTab(tr("Ecl."));
	tabBar_->setTabData(0, dm_Longitude);
	tabBar_->addTab(tr("Abs."));
	tabBar_->setTabData(1, dm_Absolute);
	tabBar_->addTab(tr("R.A."));
	tabBar_->setTabData(2, dm_RectAsc);
	tabBar_->addTab(tr("Ob.A."));
	tabBar_->setTabData(3, dm_OblAsc);
	tabBar_->addTab(tr("L/D"));
	tabBar_->setTabData(4, dm_LatDecl);
	connect(tabBar_, SIGNAL(currentChanged(int)), SLOT(tabChanged(int)));
	layout->addWidget(tabBar_);

	listMain_ = new QListView(this);
	listMain_->setEditTriggers(QListView::NoEditTriggers);
	listMain_->setUniformItemSizes(true);
	listMain_->setModel(new PlanetSelectorMainFilterModel(this, model));
	connect(this, SIGNAL(invalidateViews()), listMain_->model(), SLOT(invalidate()));
	connect(listMain_, SIGNAL(pressed(const QModelIndex&)), SLOT(listViewPressed(const QModelIndex&)));
	layout->addWidget(listMain_);

	listSecondary_ = new QListView(this);
	listSecondary_->setEditTriggers(QListView::NoEditTriggers);
	listSecondary_->setUniformItemSizes(true);
	listSecondary_->setModel(new PlanetSelectorSecondaryFilterModel(this, model));
	connect(this, SIGNAL(invalidateViews()), listSecondary_->model(), SLOT(invalidate()));
	connect(listSecondary_, SIGNAL(pressed(const QModelIndex&)), SLOT(listViewPressed(const QModelIndex&)));
	layout->addWidget(listSecondary_);

	tabChanged(tabBar_->currentIndex());
}

void PlanetSelector::setDelegate(QListView* listView, int fontSize, int property)
{
	QAbstractItemDelegate* old = listView->itemDelegate();
	listView->setFont(*GlyphManager::get_const_instance().font(fontSize, FF_ASTRO));
	listView->setItemDelegate(new PlanetSelectorDelegate(this, property, fontSize));
	delete old;
}
