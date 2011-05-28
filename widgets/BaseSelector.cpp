#include "BaseSelector.h"
#include "BaseSelectorDelegate.h"
#include "../utils/constants.h"
#include "../utils/BodyProps.h"
#include "../utils/SettingsManager.h"
#include <QTabBar>
#include <QListView>
#include <QDebug>
#include <QApplication>
#include <QSortFilterProxyModel>

BaseSelector::BaseSelector(QWidget *parent, QAbstractItemModel* model)
: QWidget(parent)
, model_(model)
, delegate_(NULL)
, listFontSize_(12)
{
}

BaseSelector::~BaseSelector()
{
	delete tabBar_;
	delete listMain_;
	delete listSecondary_;
}

void BaseSelector::tabChanged(int index)
{
	QFont* font = SettingsManager::get_const_instance().font(listFontSize_, FF_ASTRO);
	listMain_->setFont(*font);
	BaseSelectorDelegate* delegate = dynamic_cast<BaseSelectorDelegate*>(listMain_->itemDelegate());
	delegate->restyle(tabBar_->tabData(index).toInt(), listFontSize_);
	listSecondary_->setFont(*font);
	delegate = dynamic_cast<BaseSelectorDelegate*>(listSecondary_->itemDelegate());
	delegate->restyle(tabBar_->tabData(index).toInt(), listFontSize_);
	emit invalidateViews();
}

void BaseSelector::listMainPressed(const QModelIndex& index)
{
	listViewPressed (listMain_, index);
}

void BaseSelector::listSecondaryPressed(const QModelIndex& index)
{
	listViewPressed (listSecondary_, index);
}

void BaseSelector::listViewPressed(QListView* listView, const QModelIndex& index)
{
	if (QApplication::mouseButtons() == Qt::RightButton) {
		bool isVisible = listView->model()->data(index, Qt::VisibilityRole).toBool();
		BodyProps props = listView->model()->data(index).value<BodyProps>();
		qDebug() << props.id;
		qDebug() << "right click on " << index.row() << ", was visible " << isVisible;
		QModelIndex source_index = dynamic_cast<QSortFilterProxyModel*>(listView->model())->mapToSource(index);
		model_->setData(source_index, !isVisible, Qt::VisibilityRole);
		emit invalidateViews();
	}
}

void BaseSelector::timeloc_changed()
{
	emit invalidateViews();
}

void BaseSelector::setFilterModels()
{
	listMain_->setModel(getFilterModel(MODEL_MAIN));
	listMain_->setItemDelegate(getDelegate());
	connect(this, SIGNAL(invalidateViews()), listMain_->model(), SLOT(invalidate()));
	connect(listMain_, SIGNAL(pressed(const QModelIndex&)), SLOT(listMainPressed(const QModelIndex&)));

	listSecondary_->setItemDelegate(getDelegate());
	listSecondary_->setModel(getFilterModel(MODEL_SECONDARY));
	connect(this, SIGNAL(invalidateViews()), listSecondary_->model(), SLOT(invalidate()));
	connect(listSecondary_, SIGNAL(pressed(const QModelIndex&)), SLOT(listSecondaryPressed(const QModelIndex&)));

	tabChanged(tabBar_->currentIndex());
}

