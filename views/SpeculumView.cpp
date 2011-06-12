#include "SpeculumView.h"

SpeculumView::SpeculumView(QWidget *parent) :
    QTableView(parent)
{
	setSelectionMode(QAbstractItemView::SingleSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void SpeculumView::reconfigure()
{

}
