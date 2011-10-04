#include "Aspectarium.h"
#include "AspectariumDelegate.h"
#include "../models/AspectariumProxyModel.h"
#include "../menus/AspectariumMenu.h"
#include "../utils/constants.h"
#include "../utils/Aspect.h"

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
    popupMenu_ = new AspectariumMenu(this);
}

void Aspectarium::tablePressed(const QModelIndex& index)
{
    if (QApplication::mouseButtons() == Qt::RightButton) {
		popupMenu_->init(qVariantValue<Aspect>(index.data()));
		if (!popupMenu_->isEmpty())
			popupMenu_->popup(QCursor::pos());
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
