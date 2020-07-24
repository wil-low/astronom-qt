#include "AspectariumDelegate.h"
#include "../utils/Aspect.h"
#include "../utils/AspectProps.h"
#include "../utils/DMS.h"
#include "../utils/SettingsManager.h"
#include <QFontMetrics>
#include <QPainter>
#include <QDebug>

const int AspectariumDelegate::MARGIN = 10;

AspectariumDelegate::AspectariumDelegate(QObject *parent)
: QStyledItemDelegate(parent)
{
	restyle(10, 20);
}

void AspectariumDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
		   const QModelIndex &index) const
{
	if (!index.isValid())
		return;
	painter->save();
	painter->setBrush(option.palette.foreground());
	painter->setClipRect(option.rect);
	QString text[4];
    Aspect aspect = index.data().value<Aspect>();

	const SettingsManager& sm = SettingsManager::get_const_instance();
	text[0] = aspect.body_[0].label_ + aspect.body_[1].label_;

	text[1].sprintf("%c", aspect.angleProps_ ? aspect.angleProps_->angleChar() : ' ');
	text[2].sprintf("%c", aspect.signProps_ ? aspect.signProps_->signChar() : ' ');

	DMS dms;
	dms.fromCoord(aspect.angle_);
	text[3].sprintf("%2d%c%02d\'", dms.deg(), sm.degreeSign(FF_ARIAL), dms.min());
	SettingsManager::fromBackTick(text[3]);

	QFont& astroFont = *sm.font(fontSize_, FF_ASTRO);
	QFont& textFont = *sm.font(fontSize_, FF_ARIAL);

	bool isVisible = index.data(Qt::VisibilityRole).toBool();
	QPalette::ColorGroup cg = QPalette::Active; //isVisible ? QPalette::Active : QPalette::Disabled;

	if (1 && isVisible) {
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

	rect.setRight(rect.right() + width_[1]);
	painter->drawText(rect, Qt::AlignRight | Qt::AlignCenter, text[1]);
	rect.setRight(rect.right() + width_[2]);
	painter->drawText(rect, Qt::AlignRight | Qt::AlignCenter, text[2]);

	painter->setFont(textFont);
	rect.setRight(rect.right() + width_[3]);
	painter->drawText(rect, Qt::AlignRight | Qt::AlignCenter, text[3]);

	painter->restore();
}

void AspectariumDelegate::restyle(int fontSize, int height)
{
	fontSize_ = fontSize;
	height_ = height;
	const SettingsManager& sm = SettingsManager::get_const_instance();
	QFontMetrics astroFM(*sm.font(fontSize_, FF_ASTRO));
	width_[0] = astroFM.width("0000");
	width_[1] = width_[2] = astroFM.width("00");
	QFontMetrics textFM(*sm.font(fontSize_, FF_ARIAL));
	width_[3] = textFM.width("0000`00'`");
}

QSize AspectariumDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	return QSize(width_[0] + width_[1] + width_[2] + width_[3] + MARGIN, height_);
}

int AspectariumDelegate::height() const
{
	return height_;
}

