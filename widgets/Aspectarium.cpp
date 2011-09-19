#include "Aspectarium.h"
#include "AspectariumDelegate.h"
#include "../utils/constants.h"

#include <QApplication>

Aspectarium::Aspectarium(QWidget *parent, QAbstractItemModel* model)
: QTableView(parent)
{
	setModel(model);
	setItemDelegate(new AspectariumDelegate(this));
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
