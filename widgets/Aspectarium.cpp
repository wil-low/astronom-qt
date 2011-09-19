#include "Aspectarium.h"
#include "AspectariumDelegate.h"

Aspectarium::Aspectarium(QWidget *parent, QAbstractItemModel* model)
: QTableView(parent)
{
	setModel(model);
	setItemDelegate(new AspectariumDelegate(this));
}
