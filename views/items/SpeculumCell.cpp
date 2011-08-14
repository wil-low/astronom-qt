#include "SpeculumCell.h"

#include "../colors/SpeculumColors.h"
#include "../../labels/AstroLabel.h"
#include "../../utils/SettingsManager.h"

#include <boost/foreach.hpp>
#include <QPainter>

SpeculumCell::SpeculumCell(int column, int row, const SpeculumColors* colors)
: column_(column)
, row_(row)
, colors_(colors)
{
}

void SpeculumCell::reconfigure(qreal cellWidth, qreal cellHeight, int fontSize)
{
	cellWidth_ = cellWidth;
	cellHeight_ = cellHeight;
	fontSize_ = fontSize;
	rect_.setRect(cellWidth_ * column_, cellHeight_ * row_,
				  cellWidth_, cellHeight_);
	for (int category = cat_First; category < cat_Last; ++category) {
//		std::sort(labels_[category]);
		int x = (category == cat_Second) ? cellWidth_ - fontSize_ : fontSize_;
		int y = (category == cat_Second) ? cellHeight_ - fontSize_ / 2 : fontSize_ / 2;
		BOOST_FOREACH (AstroLabel* al, labels_[category]) {
			al->setFont(SettingsManager::get_const_instance().font(fontSize_, FF_ASTRO));
			//qDebug() << "Prop:" << al->type() << al->angle() << dms.zodiac() << dms.zod_deg();

			al->position(rect_.left() + x, rect_.top() + y);
			if (category == cat_Second)
				x -= fontSize_;
			else
				x += fontSize_;
		}
	}
}

void SpeculumCell::clear()
{
	for (int category = cat_First; category < cat_Last; ++category)
		labels_[category].clear();
}

void SpeculumCell::addLabel(SpeculumCell::category_t category, AstroLabel* label)
{
	labels_[category].push_back(label);
}

void SpeculumCell::draw(QPainter* painter)
{
	painter->save();
	for (int category = cat_First; category < cat_Last; ++category) {
		BOOST_FOREACH(AstroLabel* al, labels_[category]) {
			al->drawOnParent(painter);
		}
	}
	painter->restore();
}
