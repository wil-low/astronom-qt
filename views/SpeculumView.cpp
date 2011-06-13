#include "SpeculumView.h"
#include "../widgets/SpeculumItemDelegate.h"
#include "../utils/BodyProps.h"

SpeculumView::SpeculumView(QWidget *parent) :
    QTableView(parent)
{
	setSelectionMode(QAbstractItemView::SingleSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setItemDelegate(new SpeculumItemDelegate());
}

void SpeculumView::reconfigure()
{

}

void SpeculumView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
	QAbstractItemView::dataChanged(topLeft, bottomRight);
	int chart_id = 0;
	for (int row = 0; row < model()->rowCount(rootIndex()); ++row) {
		QModelIndex index = model()->index(row, chart_id, rootIndex());
		BodyProps props = model()->data(index).value<BodyProps>();
	}
}
