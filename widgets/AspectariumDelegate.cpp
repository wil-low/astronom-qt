#include "AspectariumDelegate.h"
#include "../utils/Aspect.h"
#include "../utils/AspectProps.h"
#include "../utils/DMS.h"
#include "../utils/SettingsManager.h"
#include <QFontMetrics>
#include <QPainter>
#include <QDebug>

AspectariumDelegate::AspectariumDelegate(QObject *parent)
: QStyledItemDelegate(parent)
{
	restyle(12);
}

void AspectariumDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
		   const QModelIndex &index) const
{
	painter->save();
	painter->setBrush(option.palette.foreground());
	painter->setClipRect(option.rect);
	QString text[3];
	Aspect aspect = qVariantValue<Aspect>(index.data());

	const SettingsManager& sm = SettingsManager::get_const_instance();
	text[0] = aspect.body_[0].label_ + aspect.body_[1].label_;

	DMS dms;
	dms.fromCoord(aspect.angle_);
	text[1].sprintf("%2d%c%02d\'%02d\"", dms.deg(), sm.degreeSign(FF_ARIAL), dms.min(), dms.sec());
	SettingsManager::fromBackTick(text[1]);

	text[2].sprintf("%c%c", aspect.angleProps_->angleChar(),
					aspect.signProps_ ? aspect.signProps_->signChar() : '-');

	QFont& astroFont = *sm.font(fontSize_, FF_ASTRO);
	QFont& textFont = *sm.font(fontSize_, FF_ARIAL);

	bool isVisible = index.data(Qt::VisibilityRole).toBool();
	QPalette::ColorGroup cg = isVisible ? QPalette::Active : QPalette::Disabled;

	if (isVisible) {
		if ((option.state & QStyle::State_Selected)) {
			painter->fillRect(option.rect, option.palette.brush(cg, QPalette::Highlight));
			painter->setPen(option.palette.color(cg, QPalette::HighlightedText));
		}
		else {
			painter->fillRect(option.rect, option.palette.brush(cg, QPalette::Base));
			painter->setPen(option.palette.color(cg, QPalette::WindowText));
		}
	}
	else {
		if ((option.state & QStyle::State_Selected)) {
			painter->fillRect(option.rect, option.palette.brush(cg, QPalette::WindowText));
			painter->setPen(option.palette.color(cg, QPalette::BrightText));
		}
		else {
			painter->fillRect(option.rect, option.palette.brush(cg, QPalette::Base));
			painter->setPen(option.palette.color(cg, QPalette::WindowText));
		}
	}

	QRect rect = option.rect;

	painter->setFont(astroFont);
	rect.setRight(rect.x() + width_[0]);
	painter->drawText(rect, Qt::AlignRight | Qt::AlignCenter, text[0]);

	painter->setFont(textFont);
	rect.setRight(rect.right() + width_[1]);
	painter->drawText(rect, Qt::AlignRight | Qt::AlignCenter, text[1]);

	painter->setFont(astroFont);
	rect.setRight(rect.right() + width_[2]);
	painter->drawText(rect, Qt::AlignRight | Qt::AlignCenter, text[2]);

	painter->restore();
}

void AspectariumDelegate::restyle(int fontSize)
{
	fontSize_ = fontSize;
	const SettingsManager& sm = SettingsManager::get_const_instance();
	QFontMetrics astroFM(*sm.font(fontSize_, FF_ASTRO));
	width_[0] = width_[2] = astroFM.width("0000");
	QFontMetrics textFM(*sm.font(fontSize_, FF_ARIAL));
	width_[1] = textFM.width("0000`00'`00\"");
}
