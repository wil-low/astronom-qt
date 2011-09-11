#include "Aspectarium.h"

Aspectarium::Aspectarium(QWidget *parent, QAbstractItemModel* model)
: QTableView(parent)
{
	setModel(model);
}
