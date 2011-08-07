#include "SpeculumView.h"
#include "../utils/BodyProps.h"
#include "../labels/AstroLabelContainer.h"
#include "../labels/LabelFactory.h"
#include "../labels/AspectLabel.h"
#include "../utils/SettingsManager.h"
#include "../utils/DMS.h"
#include "items/SpeculumCell.h"

#include <boost/foreach.hpp>

#include <QPainter>
#include <QDebug>

const int PLANET_FONT_SIZE = 10;
const int DEFAULT_FONT_SIZE = 10;

SpeculumView::SpeculumView(QWidget *parent)
: CentralView(parent, cv_Speculum)
, cellWidth_(0)
, cellHeight_(0)
{
	setSelectionMode(QAbstractItemView::SingleSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	for (int column = 0; column < COLUMN_COUNT; ++column)
		for (int row = 0; row < ROW_COUNT; ++row) {
			cells_[row * COLUMN_COUNT + column] = new SpeculumCell(column, row);
		}
}

SpeculumView::~SpeculumView()
{
	BOOST_FOREACH(SpeculumCell* cell, cells_)
		delete cell;
}

void SpeculumView::reconfigure()
{
	BOOST_FOREACH(SpeculumCell* cell, cells_)
		cell->reconfigure(cellWidth_, cellHeight_, DEFAULT_FONT_SIZE);
//	viewport()->update();
}

void SpeculumView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
	QAbstractItemView::dataChanged(topLeft, bottomRight);
//	qDebug() << __FUNCTION__ << topLeft.column() << "/" << topLeft.row()
//			<< ", " << bottomRight.column() << "/" << bottomRight.row();
	clearCells();
	int chart_id = 0;
	for (int row = 0; row < model()->rowCount(rootIndex()); ++row) {
		QModelIndex index = model()->index(row, chart_id, rootIndex());
		BodyProps props = model()->data(index).value<BodyProps>();
		bool isVisible = index.data(Qt::VisibilityRole).toBool();
		if (props.type == TYPE_HOUSE) {
			props.flags |= FLG_ARABIC;
			AstroLabel* label = insertLabel(chart_id, props, isVisible);
		}
		else if (props.type == TYPE_PLANET) {
			AstroLabel* label = insertLabel(chart_id, props, isVisible);
			addAspects(label);
		}
	}
	reconfigure();
}

void SpeculumView::paintEvent(QPaintEvent* event)
{
	QPainter painter(viewport());

	painter.save();
	painter.translate(0, cellHeight_);
	QLineF horizLine (0, 0, viewport()->width(), 0);
	for (int i = 0; i < ROW_COUNT; ++i) {
		painter.drawLine(horizLine);
		horizLine.translate(0, cellHeight_);
	}
	painter.restore();
	painter.save();
	painter.translate(cellWidth_, 0);
	QLineF vertLine (0, 0, 0, viewport()->height());
	for (int i = 0; i < COLUMN_COUNT; ++i) {
		painter.drawLine(vertLine);
		vertLine.translate(cellWidth_, 0);
	}
	painter.restore();
	drawHeaders(&painter);
//	painter.translate(cellWidth_, cellHeight_);
	drawCells(&painter);
}

QModelIndex SpeculumView::indexAt(const QPoint &point) const
{
	AstroLabel* cur_al = NULL;
	BOOST_FOREACH (AstroLabel* al, *labels_) {
		if (al->visible() && al->contains(point)) {
			cur_al = al;
			break;
		}
	}
	if (cur_al) {
		int chart_id = cur_al->chartId();
		int id = cur_al->id();
		int rowCount = model()->rowCount();
		for (int i = 0; i < rowCount; ++i) {
			QModelIndex index = model()->index(i, chart_id);
			const BodyProps& props = model()->data(index).value<BodyProps>();
			if (props.id == id)
				return index;
		}
	}
	return QModelIndex();
}

bool SpeculumView::isIndexHidden(const QModelIndex &index) const
{
	return false;
}

void SpeculumView::drawCells (QPainter* painter)
{
	BOOST_FOREACH (SpeculumCell* cell, cells_) {
		cell->draw(painter);
//		qDebug() << "draw " << al->toString() << ", text '" << al->text() << ", " << al->rect();
	}
}

void SpeculumView::resizeEvent (QResizeEvent* event)
{
	cellWidth_ = (qreal)viewport()->width() / (COLUMN_COUNT + 1);
	cellHeight_ = (qreal)viewport()->height() / (ROW_COUNT + 1);
	reconfigure();
}

void SpeculumView::drawHeaders (QPainter* painter)
{
	painter->save();
	painter->setFont(*SettingsManager::get_const_instance().font(DEFAULT_FONT_SIZE, FF_ASTRO));
	painter->translate(cellWidth_, 0);
	painter->setPen(Qt::darkCyan);
	for (int i = 0; i < COLUMN_COUNT; ++i) {
		BodyProps bp(TYPE_ZODIAC, i);
		painter->drawText(QRect(i * cellWidth_, 0, cellWidth_, cellHeight_),
						  Qt::AlignHCenter | Qt::TextDontClip,
						  SettingsManager::get_const_instance().label(bp));
	}
	painter->restore();
	painter->save();
	painter->setFont(*SettingsManager::get_const_instance().font(DEFAULT_FONT_SIZE, FF_ARIAL));
	painter->translate(0, cellHeight_);
	for (int i = 0; i < ROW_COUNT; ++i) {
		painter->drawText(QRect(0, i * cellHeight_, cellWidth_, cellHeight_),
						  Qt::AlignHCenter | Qt::TextDontClip,
						  QString::number(i + 1));
	}
	painter->restore();
}

void SpeculumView::clearCells()
{
	BOOST_FOREACH(SpeculumCell* cell, cells_)
		cell->clear();
}

AstroLabel* SpeculumView::insertLabel(int chart_id, const BodyProps& props, bool isVisible)
{
	AstroLabel* label = labels_->find_by_chart_id(chart_id, props.id);
	bool need_insert = !label;
	if (!label)
		label = LabelFactory::construct(this, chart_id, props);
	label->setProps(props);
	label->setChartId(chart_id);
	label->setVisible(isVisible);
	if (need_insert) {
		std::pair<AlcIter, bool> result = labels_->insert(label);
		assert (result.second);
	}
	DMS dms(props.prop[BodyProps::bp_Lon], DMS::COORD_LON);
	int column = dms.zodiac();
	int row = dms.zod_deg();
	cells_[row * COLUMN_COUNT + column]->addLabel(SpeculumCell::cat_First, label);
	return label;
}

void SpeculumView::addAspects (AstroLabel* parentLabel)
{
	static const double ASPECT_ANGLES[] = {
		180, 120, 90, 60,
	};
	BOOST_FOREACH(const double& angle, ASPECT_ANGLES) {
		BodyProps props;
		props.type = TYPE_ASPECT;
		props.userData = (int)angle;
		props.prop[BodyProps::bp_AspectAngle] = angle;
		// positive angle
		props.id = AspectLabel::calculateId(parentLabel->id(), parentLabel->id(), (int)angle);
		props.prop[BodyProps::bp_Lon] = BodyProps::normalize(
				parentLabel->prop(BodyProps::bp_Lon) + angle, ZODIAC_SIGN_COUNT * DEG_PER_SIGN);
		insertLabel(parentLabel->chartId(), props, parentLabel->visible());
		// negative angle
		if ((int)angle != 180) {
			props.id = AspectLabel::calculateId(parentLabel->id(), parentLabel->id(), (int)-angle);
			props.prop[BodyProps::bp_Lon] = BodyProps::normalize(
					parentLabel->prop(BodyProps::bp_Lon) - angle, ZODIAC_SIGN_COUNT * DEG_PER_SIGN);
			insertLabel(parentLabel->chartId(), props, parentLabel->visible());
		}
	}
}

