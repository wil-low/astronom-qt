#include "SpeculumItemDelegate.h"
#include "../utils/BodyProps.h"
#include "../utils/SettingsManager.h"
#include <QPainter>

SpeculumItemDelegate::SpeculumItemDelegate(QObject *parent) :
	QStyledItemDelegate(parent)
{
}

void SpeculumItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
		   const QModelIndex &index) const
{
	const int SIDE_MARGIN = 10;
	painter->save();
	painter->setBrush(option.palette.foreground());

	QString text[3];
	BodyProps props = qVariantValue<BodyProps>(index.data());

	const SettingsManager& sm = SettingsManager::get_const_instance();
	text[0] = sm.label(props);
	QRect rect = option.rect;
	painter->drawText(rect, text[0]);
	painter->restore();
}

QSize SpeculumItemDelegate::sizeHint(const QStyleOptionViewItem &option,
							 const QModelIndex &index) const
{
	return QStyledItemDelegate::sizeHint(option, index);
}
