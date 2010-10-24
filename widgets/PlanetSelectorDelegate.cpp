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
	painter->setFont(option.font);
	BodyProps props = qVariantValue<BodyProps>(index.data());
	QString s;
	s.sprintf("%d: %f", props.id, props.prop[BodyProps::bp_Lon]);
	if (option.state & QStyle::State_Selected) {
		painter->fillRect(option.rect, option.palette.highlight());
		painter->setPen(option.palette.color(QPalette::HighlightedText));
	}
	painter->drawText(option.rect, s);
	painter->restore();
}

QSize PlanetSelectorDelegate::sizeHint(const QStyleOptionViewItem &option,
							 const QModelIndex &index) const
{
	return QStyledItemDelegate::sizeHint(option, index);
}
