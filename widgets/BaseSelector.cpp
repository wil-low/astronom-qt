#include "BaseSelector.h"
#include <QTabBar>
#include <QListView>
#include <QDebug>
#include <QApplication>

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

void BaseSelector::listViewPressed(const QModelIndex& index)
{
	if (QApplication::mouseButtons() == Qt::RightButton) {
		qDebug() << "right click on " << index.row();
	}
}

void BaseSelector::timeloc_changed()
{
	emit invalidateViews();
}
