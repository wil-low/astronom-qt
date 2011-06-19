#include "SpeculumView.h"
#include "../utils/BodyProps.h"
#include "../labels/AstroLabelContainer.h"
#include "../labels/LabelFactory.h"
#include "../utils/SettingsManager.h"
#include "../utils/DMS.h"

#include <boost/foreach.hpp>

#include <QPainter>
#include <QDebug>

const int COLUMN_COUNT = 12;
const int ROW_COUNT = 30;
const int HORIZONTAL_HEADER_HEIGHT = 20;
const int VERTICAL_HEADER_WIDTH = 20;

SpeculumView::SpeculumView(QWidget *parent)
: QAbstractItemView(parent)
, labels_(new AstroLabelContainer)
, cellWidth_(0)
, cellHeight_(0)
{
	setSelectionMode(QAbstractItemView::SingleSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
}

SpeculumView::~SpeculumView()
{
	delete labels_;
}

void SpeculumView::reconfigure()
{
	reorderLabels();
//	viewport()->update();
}

void SpeculumView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
	QAbstractItemView::dataChanged(topLeft, bottomRight);
	int chart_id = 0;
	for (int row = 0; row < model()->rowCount(rootIndex()); ++row) {
		QModelIndex index = model()->index(row, chart_id, rootIndex());
		BodyProps props = model()->data(index).value<BodyProps>();
		bool isVisible = index.data(Qt::VisibilityRole).toBool();
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
	}
}

void SpeculumView::paintEvent(QPaintEvent* event)
{
	QPainter painter(viewport());

	painter.save();
	painter.translate(0, HORIZONTAL_HEADER_HEIGHT);
	QLineF horizLine (0, 0, viewport()->width(), 0);
	for (int i = 0; i < ROW_COUNT; ++i) {
		painter.drawLine(horizLine);
		horizLine.translate(0, cellHeight_);
	}
	painter.restore();
	painter.save();
	painter.translate(VERTICAL_HEADER_WIDTH, 0);
	QLineF vertLine (0, 0, 0, viewport()->height());
	for (int i = 0; i < COLUMN_COUNT; ++i) {
		painter.drawLine(vertLine);
		vertLine.translate(cellWidth_, 0);
	}
	painter.restore();
	painter.translate(VERTICAL_HEADER_WIDTH, HORIZONTAL_HEADER_HEIGHT);
	drawLabels(&painter);
}

QRect SpeculumView::visualRect(const QModelIndex &index) const
{
	return QRect();
}

void SpeculumView::scrollTo(const QModelIndex &index, ScrollHint hint)
{

}

QModelIndex SpeculumView::indexAt(const QPoint &point) const
{
	return QModelIndex();
}

void SpeculumView::currentChanged (const QModelIndex & current, const QModelIndex & previous)
{

}

QModelIndex SpeculumView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
	return QModelIndex();
}

int SpeculumView::horizontalOffset() const
{
	return 0;
}

int SpeculumView::verticalOffset() const
{
	return 0;
}

bool SpeculumView::isIndexHidden(const QModelIndex &index) const
{
	return false;
}

void SpeculumView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
	//qDebug() << rect;
}

QRegion SpeculumView::visualRegionForSelection(const QItemSelection &selection) const
{
	return QRegion();
}

void SpeculumView::drawLabels (QPainter* painter)
{
	BOOST_FOREACH (AstroLabel* al, *labels_) {
		al->drawOnParent(painter);
//		qDebug() << "draw " << al->toString() << ", text '" << al->text() << ", " << al->rect();
	}
}

void SpeculumView::reorderLabels()
{
	qDebug() << __FUNCTION__;
	BOOST_FOREACH (AstroLabel* al, *labels_) {
		int font_size;
		switch (al->type()) {
			case TYPE_PLANET:
				font_size = 10;
				break;
			default:
				font_size = 8;
		}
		al->setFont(SettingsManager::get_const_instance().font(font_size, FF_ASTRO));
		DMS dms(al->angle(), DMS::COORD_LAT);
		qDebug() << "Prop:" << al->type() << al->angle() << dms.zodiac() << dms.zod_deg();
		al->position(dms.zodiac() * cellWidth_, dms.zod_deg() * cellHeight_);
	}
	/*
	qreal rad[TYPE_LAST];
	rad[TYPE_ZODIAC] = (dimensions_[ODIM_zodiac10dgrR] + dimensions_[ODIM_zodiac5dgrR]) / 2;
	rad[TYPE_PLANET] = dimensions_[ODIM_innerPlanetLabelR];
	rad[TYPE_HOUSE] = 10000000;
	QPointF pt;

	spreadLabels(0, TYPE_PLANET, rad[TYPE_PLANET]);
//	spreadLabels(1, TYPE_PLANET, rad[TYPE_PLANET]);
//	spreadLabels(0, TYPE_HOUSE, rad[TYPE_HOUSE]);
	BOOST_FOREACH (AstroLabel* al, *labels_) {
		qreal ang = al->visibleAngle();
		pt = DrawHelper::getXYdeg(zeroAngle_ + al->visibleAngle(), rad[al->type()]);
		al->position(pt.x(), pt.y());
	}*/
}

void SpeculumView::resizeEvent (QResizeEvent* event)
{
	qreal view_w = viewport()->width() - VERTICAL_HEADER_WIDTH;
	qreal view_h = viewport()->height() - HORIZONTAL_HEADER_HEIGHT;
	cellWidth_ = view_w / COLUMN_COUNT;
	cellHeight_ = view_h / ROW_COUNT;

	reconfigure();
}
