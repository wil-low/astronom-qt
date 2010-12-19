#include "BaseSelector.h"
#include "../utils/constants.h"
#include "../utils/BodyProps.h"
#include <QTabBar>
#include <QListView>
#include <QDebug>
#include <QApplication>
#include <QSortFilterProxyModel>

BaseSelector::BaseSelector(QWidget *parent, QAbstractItemModel* model)
: QWidget(parent)
, model_(model)
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
	setDelegate(listMain_, listFontSize_, tabBar_->tabData(index).toInt());
	setDelegate(listSecondary_, listFontSize_, tabBar_->tabData(index).toInt());
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
