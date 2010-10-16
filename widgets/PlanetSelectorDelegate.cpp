#include "PlanetSelectorDelegate.h"
#include "../utils/BodyProps.h"
#include <QPainter>
#include <QDebug>

PlanetSelectorDelegate::PlanetSelectorDelegate(QObject *parent) :
	QStyledItemDelegate(parent)
{
}

void PlanetSelectorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
		   const QModelIndex &index) const
{
	painter->save();
	painter->setBrush(option.palette.foreground());
	BodyProps props = qVariantValue<BodyProps>(index.data());
	QString s;
	s.sprintf("%d: %f", props.id, props.prop[BodyProps::bp_Lon]);
	qDebug() << "paint " << s;
	painter->drawText(0, 20, s);
	painter->restore();
}

QSize PlanetSelectorDelegate::sizeHint(const QStyleOptionViewItem &option,
							 const QModelIndex &index) const
{
	return QStyledItemDelegate::sizeHint(option, index);
}
