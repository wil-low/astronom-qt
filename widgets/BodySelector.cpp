#include "BodySelector.h"
#include "BodySelectorDelegate.h"
#include "../utils/constants.h"
#include <QVBoxLayout>
#include <QTabBar>
#include <QListView>

BodySelector::BodySelector(QWidget *parent, QAbstractItemModel* model)
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
	layout->addWidget(listMain_);

	listSecondary_ = new QListView(this);
	listSecondary_->setEditTriggers(QListView::NoEditTriggers);
	listSecondary_->setUniformItemSizes(true);
	layout->addWidget(listSecondary_);
}

BaseSelectorDelegate* BodySelector::getDelegate()
{
	if (delegate_ == NULL)
		delegate_ = new BodySelectorDelegate(this);
	return delegate_;
}
