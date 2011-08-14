#include "SpeculumHorizHeader.h"
#include "../colors/SpeculumColors.h"
#include "../../utils/SettingsManager.h"
#include "../../utils/constants.h"
#include "../../utils/BodyProps.h"
#include <QPainter>

SpeculumHorizHeader::SpeculumHorizHeader(int column, int row, const SpeculumColors* colors)
: SpeculumCell(column, row, colors)
{
}

void SpeculumHorizHeader::draw(QPainter* painter)
{
	painter->save();
	painter->setFont(*SettingsManager::get_const_instance().font(speculum::DEFAULT_FONT_SIZE, FF_ASTRO));
	painter->setPen(colors_->headerColor);
	BodyProps bp(TYPE_ZODIAC, column_ - 1);
	painter->drawText(rect_, Qt::AlignHCenter | Qt::TextDontClip,
					  SettingsManager::get_const_instance().label(bp));
	painter->restore();
}
