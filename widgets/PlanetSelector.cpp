#include "PlanetSelector.h"
#include "PlanetSelectorDelegate.h"
#include "utils/constants.h"
#include "../utils/GlyphManager.h"
#include <QVBoxLayout>
#include <QTabBar>
#include <QListView>
#include <QDebug>
#include <QApplication>

PlanetSelector::PlanetSelector(QWidget *parent, QAbstractItemModel* model)
: QWidget(parent)
, listFontSize_(12)
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	tabBar_ = new QTabBar(this);
	tabBar_->addTab(tr("Abs."));
	tabBar_->setTabData(0, dm_Absolute);
	tabBar_->addTab(tr("Ecl."));
	tabBar_->setTabData(1, dm_Longitude);
	tabBar_->addTab(tr("R.A."));
	tabBar_->setTabData(2, dm_RectAsc);
	tabBar_->addTab(tr("Ob.A."));
	tabBar_->setTabData(3, dm_OblAsc);
	tabBar_->addTab(tr("L/D"));
	tabBar_->setTabData(4, dm_LatDecl);
	connect(tabBar_, SIGNAL(currentChanged(int)), SLOT(tabChanged(int)));

	listView_ = new QListView(this);
	listView_->setEditTriggers(QListView::NoEditTriggers);
	listView_->setUniformItemSizes(true);
	layout->addWidget(tabBar_);
	layout->addWidget(listView_);
	listView_->setModel(model);
	connect(listView_, SIGNAL(pressed(const QModelIndex&)), SLOT(listViewPressed(const QModelIndex&)));

	setDelegate(listFontSize_, tabBar_->tabData(tabBar_->currentIndex()).toInt());
}

PlanetSelector::~PlanetSelector()
{
	delete tabBar_;
	delete listView_;
}

void PlanetSelector::setDelegate(int fontSize, int property)
{
	QAbstractItemDelegate* old = listView_->itemDelegate();
	listView_->setFont(*GlyphManager::get_const_instance().font(fontSize, FF_ASTRO));
	listView_->setItemDelegate(new PlanetSelectorDelegate(this, property, fontSize));
	delete old;
}

void PlanetSelector::tabChanged(int index)
{
	setDelegate(listFontSize_, tabBar_->tabData(index).toInt());
}

void PlanetSelector::listViewPressed(const QModelIndex& index)
{
	if (QApplication::mouseButtons() == Qt::RightButton) {
		qDebug() << "right click on " << index.row();
	}
}
