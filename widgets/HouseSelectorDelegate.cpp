#include "HouseSelectorDelegate.h"
#include "../utils/BodyProps.h"
#include "../utils/DMS.h"
#include "../utils/SettingsManager.h"
#include <QPainter>
#include <QDebug>

HouseSelectorDelegate::HouseSelectorDelegate(QObject *parent)
: BaseSelectorDelegate(parent)
{
}

void HouseSelectorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
		   const QModelIndex &index) const
{
	const int SIDE_MARGIN = 10;
	painter->save();
	painter->setBrush(option.palette.foreground());

	QString text[3];
	BodyProps props = qVariantValue<BodyProps>(index.data());

	const SettingsManager& sm = SettingsManager::get_const_instance();
	text[0] = sm.label(props);
	text[1] = text[2] = "";

	DMS dms;
	switch (degree_mode_) {
	case dm_Absolute:
		dms.fromCoord(props.prop[BodyProps::bp_Lon]);
		text[1].sprintf("%3d%c%02d\'%02d\"", dms.deg(), sm.degreeSign(FF_ARIAL), dms.min(), dms.sec());
		break;
	case dm_Longitude: {
		dms.fromCoord(props.prop[BodyProps::bp_Lon]);
		text[1].sprintf("%2d%c%02d\'%02d\"", dms.zod_deg(), sm.degreeSign(FF_ARIAL), dms.min(), dms.sec());
		BodyProps bp(TYPE_ZODIAC, dms.zodiac());
		text[2] = sm.label(bp);
		break;}
	case dm_RectAsc:
		dms.fromCoord(props.prop[BodyProps::bp_RectAsc]);
		text[1].sprintf("%3d%c%02d\'%02d\"", dms.deg(), sm.degreeSign(FF_ARIAL), dms.min(), dms.sec());
		break;
	case dm_OblAsc:
		dms.fromCoord(props.prop[BodyProps::bp_OblAsc]);
		text[1].sprintf("%3d%c%02d\'%02d\"", dms.deg(), sm.degreeSign(FF_ARIAL), dms.min(), dms.sec());
		break;
	case dm_LatDecl:
		dms.fromCoord(props.prop[BodyProps::bp_Lat]);
		text[1].sprintf("%3d%c%02d\'%02d\"", dms.deg(), sm.degreeSign(FF_ARIAL), dms.min(), dms.sec());
		break;
	}
	SettingsManager::fromBackTick(text[1]);

	if (option.state & QStyle::State_Selected) {
		painter->fillRect(option.rect, option.palette.highlight());
		painter->setPen(option.palette.color(QPalette::HighlightedText));
	}

	QFont& astroFont = *sm.font(fontSize_, FF_ASTRO);
	QFont& textFont = *sm.font(fontSize_, FF_ARIAL);

	painter->setFont(astroFont);
	QRectF maxDegreeRect = painter->boundingRect(option.rect, "-000`00'`00\"");

	painter->setFont(props.type == TYPE_HOUSE ? textFont : astroFont);

	QRect rect = option.rect;
	rect.setX(SIDE_MARGIN);

	painter->drawText(rect, text[0]);


	if (!text[1].isEmpty()) {
		painter->setFont(textFont);
		rect.setRight(maxDegreeRect.width() + SIDE_MARGIN + rect.height());
		painter->drawText(rect, Qt::AlignRight, text[1]);
	}

	if (!text[2].isEmpty()) {
		painter->setFont(astroFont);
		rect.setRight(option.rect.right() - SIDE_MARGIN);
		painter->drawText(rect, Qt::AlignRight, text[2]);
	}

	painter->restore();
}
