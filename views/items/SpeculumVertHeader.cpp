#include "SpeculumVertHeader.h"
#include "../colors/SpeculumColors.h"
#include "../../utils/SettingsManager.h"
#include "../../utils/constants.h"
#include "../../utils/BodyProps.h"
#include "../../labels/AstroLabel.h"
#include <QPainter>
#include <QDebug>
#include <boost/foreach.hpp>

SpeculumVertHeader::SpeculumVertHeader(int column, int row, const SpeculumColors* colors)
: SpeculumCell(column, row, colors)
{
}

void SpeculumVertHeader::draw(QPainter* painter)
{
	painter->save();
	painter->setFont(*SettingsManager::get_const_instance().font(DEFAULT_FONT_SIZE, FF_ASTRO));
	painter->setPen(colors_->headerColor);
	painter->drawText(rect_, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextDontClip, QString::number(row_));
	painter->restore();
/*	painter->drawText(rect_, QString::number(labels_[cat_First].size()) + "+" +
					  QString::number(labels_[cat_Second].size()));

	BOOST_FOREACH(AstroLabel* al, labels_[cat_Second]) {
		al->drawOnParent(painter);
	}*/
	SpeculumCell::draw(painter);
}
