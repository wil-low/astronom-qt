#include "Aspectarium.h"
#include "AspectariumDelegate.h"
#include "../models/AspectariumProxyModel.h"
#include "../utils/constants.h"

#include <QApplication>
#include <QHeaderView>
#include <QResizeEvent>

Aspectarium::Aspectarium(QWidget *parent, QAbstractItemModel* model)
: QTableView(parent)
{
	proxyModel_ = new AspectariumProxyModel(this, model);
	setModel(proxyModel_);
	setItemDelegate(new AspectariumDelegate(this));
	horizontalHeader()->hide();
	verticalHeader()->hide();
	connect(this, SIGNAL(pressed(const QModelIndex&)), SLOT(tablePressed(const QModelIndex&)));
}

void Aspectarium::tablePressed(const QModelIndex& index)
{
	if (QApplication::mouseButtons() == Qt::RightButton) {
		bool isVisible = model()->data(index, Qt::VisibilityRole).toBool();
		model()->setData(index, !isVisible, Qt::VisibilityRole);
		emit invalidate();
	}
}

void Aspectarium::resizeEvent(QResizeEvent* event)
{
	QSize newSize = event->size();
	AspectariumDelegate* delegate = dynamic_cast<AspectariumDelegate*>(itemDelegate());
	int rows = newSize.height() / (delegate->height() + 1);
	proxyModel_->setRowCount(rows > 0 ? rows : 1);
	verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
	horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}
