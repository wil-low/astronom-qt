#include "OcularDelegate.h"
#include <QDebug>
OcularDelegate::OcularDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void OcularDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
		   const QModelIndex &index) const
{
	qDebug() << index.model()->data(index, Qt::DisplayRole).toInt() << "\n";
}

QSize OcularDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	return QSize(10, 10);
}
