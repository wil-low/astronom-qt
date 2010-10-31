#include "OcularView.h"
#include "../utils/DrawHelper.h"
#include "../utils/constants.h"
#include "../labels/AstroLabelContainer.h"
#include "../labels/LabelFactory.h"
#include "../utils/GlyphManager.h"
#include "../CircleSpread/CircleSpread.h"
#include <QSettings>
#include <QPainter>
#include <QDebug>
#include <boost/foreach.hpp>

OcularView::OcularView(QWidget *parent)
: QAbstractItemView(parent)
, labels_(new AstroLabelContainer)
{
}

OcularView::~OcularView()
{
	delete labels_;
}

void OcularView::reconfigure()
{
	dimensions_[ODIM_zeroPoint] = ZERO_ARIES;
	dimensions_[ODIM_zeroAngle] = 180;

	QSettings settings;
	settings.beginGroup("ocular:dimensions");
	defaultDimensions_[ODIM_radius] = settings.value("radius", 377).toInt();
	defaultDimensions_[ODIM_ascArrowR] = settings.value("ascArrowR", 374).toInt();
	defaultDimensions_[ODIM_zodiacOuterR] = settings.value("zodiacOuterR", 300).toInt();
	defaultDimensions_[ODIM_zodiac10dgrR] = settings.value("zodiac10dgrR", 291).toInt();
	defaultDimensions_[ODIM_zodiac5dgrR] = settings.value("zodiac5dgrR", 262).toInt();
	defaultDimensions_[ODIM_innerPlanetLabelR] = settings.value("innerPlanetLabelR", 234).toInt();
	defaultDimensions_[ODIM_zodiac30dgrR] = settings.value("zodiac30dgrR", 0).toInt();
	defaultDimensions_[ODIM_innerPlanetR] = settings.value("innerPlanetR", 248).toInt();
	defaultDimensions_[ODIM_zodiacInner2R] = settings.value("zodiacInner2R", 147).toInt();
	defaultDimensions_[ODIM_zodiacInnerR] = settings.value("zodiacInnerR", 141).toInt();
	defaultDimensions_[ODIM_aspectR] = settings.value("aspectR", 374).toInt();
	defaultDimensions_[ODIM_planetFontSize] = settings.value("planetFontSize", 5).toInt();
	defaultDimensions_[ODIM_zodiacFontSize] = settings.value("zodiacFontSize", 4).toInt();
	defaultDimensions_[ODIM_degreeFontSize] = settings.value("degreeFontSize", 3).toInt();
	defaultDimensions_[ODIM_tick10Size] = settings.value("tick10Size", 8).toInt();
	defaultDimensions_[ODIM_tick5Size] = settings.value("tick5Size", 5).toInt();
	settings.endGroup();

	settings.beginGroup("ocular:colors");
	colors_.ocularColor = settings.value("ocularColor", QColor(247,240,255)).value<QColor>(); // almost grey
	colors_.contourColor = settings.value("contourColor", QColor(0,0,0)).value<QColor>(); // light violet
	colors_.mainLineColor = settings.value("mainLineColor", QColor(128,0,192)).value<QColor>();
	colors_.labelColor = settings.value("labelColor", QColor(0,0,0)).value<QColor>();
	colors_.fillColor = settings.value("fillColor", QColor(240,224,255)).value<QColor>();
	colors_.arrowColor = settings.value("arrowColor", QColor(255,0,0)).value<QColor>();
	colors_.cuspidColor = settings.value("cuspidColor", QColor(0,192,128)).value<QColor>();
	colors_.tick10Color = settings.value("tick10Color", QColor(192,0,255)).value<QColor>();
	colors_.innerRColor = settings.value("innerRColor", QColor(192,0,255)).value<QColor>();
	colors_.planetTickColor = settings.value("planetTickColor", QColor(0,192,255)).value<QColor>();
	colors_.ocularColor = settings.value("ocularColor", QColor(247,240,255)).value<QColor>();
	colors_.aspectTickColor = settings.value("aspectTickColor", QColor(0,0,0)).value<QColor>();
	settings.endGroup();

	recalcDimensions(defaultDimensions_[ODIM_radius]);

	BodyProps props;
	props.type = TYPE_ZODIAC;
	for (int i = 0; i < ZODIAC_SIGN_COUNT; ++i) {
		props.id = i;
//		QString label_text;
//		label_text.sprintf("%c", GlyphManager::get_const_instance().getLabel(TYPE_ZODIAC, i));
		labels_->insert(LabelFactory::construct(this, -1, props));
	}
//	createWheel();
//	addZodiacSigns();
	BOOST_FOREACH (AstroLabel* label, *labels_) {
		qDebug() << label->toString();
	}
//	return;
	reorderLabels();
}

void OcularView::recalcDimensions(qreal newRadius)
{
	recalcDimensionsByFactor(newRadius / defaultDimensions_[ODIM_radius]);
}

void OcularView::recalcDimensionsByFactor(qreal factor)
{
	for (int i = 0; i < ODIM_LAST; ++i)
		dimensions_[i] = defaultDimensions_[i] * factor;
	reorderLabels();
	viewport()->update();
}

void OcularView::paintEvent(QPaintEvent* event)
{
	QPainter painter(viewport());
	painter.translate(viewport()->width() / 2, viewport()->height() / 2);
	painter.fillRect(QRectF(-dimensions_[ODIM_radius], -dimensions_[ODIM_radius], dimensions_[ODIM_radius] * 2, dimensions_[ODIM_radius] * 2), QColor(Qt::white));
//	painter.setRenderHints(QPainter::Antialiasing);
	if (dimensions_[ODIM_ascArrowR] != 0) {
		painter.setPen(colors_.ocularColor);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_ascArrowR]);
	}
	qreal ang = dimensions_[ODIM_zeroAngle];
	qreal delta_ang = DEG_PER_SIGN;

	if (dimensions_[ODIM_zodiacOuterR] != 0) {
//		if (!is_resizing_) {
			ang = dimensions_[ODIM_zeroAngle];
			delta_ang = DEG_PER_SIGN;
			painter.setBrush(colors_.fillColor);
			for (int sign = 0; sign < 6; ++sign) {
				DrawHelper::drawPie(&painter, dimensions_[ODIM_zodiacOuterR], ang + delta_ang, delta_ang);
				ang += delta_ang * 2;
			}
//		}
		painter.setPen(colors_.contourColor);
		painter.setBrush(Qt::transparent);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_zodiacOuterR]);
	}

	if (dimensions_[ODIM_zodiac10dgrR] != 0) {
		painter.setPen(colors_.mainLineColor);
		painter.setBrush(Qt::white);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_zodiac10dgrR]);
	}
	if (dimensions_[ODIM_zodiac5dgrR] != 0) {
		painter.setPen(colors_.mainLineColor);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_zodiac5dgrR]);
	}
	if (dimensions_[ODIM_zodiac30dgrR] != 0) {
		painter.setPen(colors_.mainLineColor);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_zodiac30dgrR]);
	}
	if (dimensions_[ODIM_zodiacInner2R] != 0) {
//		if (!is_resizing_) {
			ang = dimensions_[ODIM_zeroAngle];
			delta_ang = DEG_PER_SIGN;
			painter.setPen(Qt::transparent);
			painter.setBrush(colors_.fillColor);
			for (int sign = 0; sign < 6; ++sign) {
				DrawHelper::drawPie(&painter, dimensions_[ODIM_zodiacInner2R], ang + delta_ang, delta_ang);
				ang += delta_ang * 2;
//			}
		}
		painter.setPen(colors_.mainLineColor);
		painter.setBrush(Qt::transparent);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_zodiacInner2R]);
	}

	if (dimensions_[ODIM_zodiacInnerR] != 0) {
		painter.setPen(colors_.mainLineColor);
		painter.setBrush(Qt::white);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_zodiacInnerR]);
	}
/*
	if (dimensions_[ODIM_aspectR != 0) {
		painter.setPen(colors_.mainLineColor);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_aspectR);
	}
*/

	painter.setPen(colors_.ocularColor);
	painter.setBrush(Qt::transparent);
	DrawHelper::drawCircle(&painter, dimensions_[ODIM_ascArrowR] * 0.06);

	// Aries line
	painter.setPen(colors_.arrowColor);

	qreal r_aries = dimensions_[ODIM_zodiacOuterR] + 1;
	ang = dimensions_[ODIM_zeroAngle];
	QPointF pt[3];
	pt[0] = DrawHelper::getXYdeg(ang - 1, r_aries * 1.02);
	pt[1] = DrawHelper::getXYdeg(dimensions_[ODIM_zeroAngle], r_aries);
	pt[2] = DrawHelper::getXYdeg(ang + 1, r_aries * 1.02);
	painter.drawPolyline(pt, 3);

	ang = dimensions_[ODIM_zeroAngle];
	delta_ang = 5;
	qreal zinner = dimensions_[ODIM_zodiac5dgrR];
	qreal zouter;
	qreal zinner1 = dimensions_[ODIM_zodiacInnerR];
	qreal zinner2 = dimensions_[ODIM_zodiacInner2R];

	QPen pen1(colors_.mainLineColor);
	pen1.setWidth(1);
	QPen pen2(colors_.mainLineColor);
	pen2.setWidth(2);
	QPointF pti[2];
	for (int tick = 0; tick < 360 / 5; ++tick) {
		pt[0] = DrawHelper::getXYdeg(ang, zinner);
		if (tick % 6 == 0) { // solid line - sign
			painter.setPen(pen1);
			pti[0] = DrawHelper::getXYdeg(ang, zinner1);
			pti[1] = DrawHelper::getXYdeg(ang, zinner2);
			painter.drawLines(pti, 1);
			painter.setPen(pen2);
			pt[1] = DrawHelper::getXYdeg(ang, zinner + dimensions_[ODIM_tick10Size]);
		}
		else {
			painter.setPen(pen1);
			pt[1] = DrawHelper::getXYdeg(ang, zinner + dimensions_[ODIM_tick5Size]);
		}
		painter.drawLines(pt, 1);
		ang += delta_ang;
	}
	painter.setPen(colors_.tick10Color);
	ang = dimensions_[ODIM_zeroAngle];
	delta_ang = 10;
	zinner = dimensions_[ODIM_zodiac10dgrR];
	zouter = dimensions_[ODIM_zodiacOuterR];
	for (int tick = 0; tick < 360 / 10; ++tick) {
		pt[0] = DrawHelper::getXYdeg(ang, zinner);
		pt[1] = DrawHelper::getXYdeg(ang, zouter);
		painter.drawLines(pt, 1);
		ang += delta_ang;
	}

	drawLabels(&painter);
	drawPlanetLines (&painter);
	drawHouseLines (&painter);
/*
	drawAspects(dc);

	drawLabels (dc);*/
}

QRect OcularView::visualRect(const QModelIndex &index) const
{
	return QRect(0,0,0,0);
}

void OcularView::scrollTo(const QModelIndex &index, ScrollHint hint)
{

}

QModelIndex OcularView::indexAt(const QPoint &point) const
{
	return QModelIndex();
}

QModelIndex OcularView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
	return QModelIndex();
}

int OcularView::horizontalOffset() const
{
	return 0;
}

int OcularView::verticalOffset() const
{
	return 0;
}

bool OcularView::isIndexHidden(const QModelIndex &index) const
{
	return false;
}

void OcularView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{

}

QRegion OcularView::visualRegionForSelection(const QItemSelection &selection) const
{
	return QRegion();
}

void OcularView::spreadLabels (int chart, int type, qreal r)
{
	std::vector<SpreadValue> input;
	qreal delta_width = 0;

	alc_by_chart_type& idx = labels_->get<chart_type_tag>();
	std::pair<alc_by_chart_type::iterator, alc_by_chart_type::iterator> range =
		idx.equal_range(boost::make_tuple(chart, (body_type_t)type));
	alc_by_chart_type::iterator it = range.first;
	while (it != range.second) {
		if ((*it)->visible()) {
			(*it)->setVisibleAngle((*it)->angle());
			input.push_back(SpreadValue((*it)->angle(), *it));
			delta_width = (*it)->rect().width() / 2;
//			FXTRACE((90, "%s\n", (*it)->toString().text()));
		}
		++it;
	}
	delta_width *= 0.68;
	qreal delta_ang = atan (delta_width / r) / DTOR * 2;
	CircleSpread cspread(input);

	std::vector<SpreadValue> output;
	//FXTRACE((90, "Delta_ang %.02f, input vector size %d\n", delta_ang, input.size()));
	cspread.spread(output, delta_ang, 360);

	BOOST_FOREACH (SpreadValue& sv, output) {
//		FXTRACE((99, "output %d->%.02f\n", (int)sv.ptr_, sv.val_));
		AstroLabel* label = static_cast<AstroLabel*>(sv.ptr_);
		label->setVisibleAngle(sv.val_);
		qDebug() << label->toString();
	}
}

void OcularView::reorderLabels()
{
	BOOST_FOREACH (AstroLabel* al, *labels_) {
		int font_size;
		switch (al->type()) {
			case TYPE_PLANET:
				font_size = 16;
				break;
			default:
				font_size = 12;
		}
		al->setFont(GlyphManager::get_const_instance().font(font_size, FF_ASTRO));
	}
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
		pt = DrawHelper::getXYdeg(dimensions_[ODIM_zeroAngle] + al->visibleAngle(), rad[al->type()]);
		al->position(pt.x(), pt.y());
	}
}

void OcularView::drawLabels (QPainter* painter)
{
	BOOST_FOREACH (AstroLabel* al, *labels_) {
		al->drawOnParent(painter);
//		qDebug() << "draw " << al->toString() << ", text '" << al->text() << ", " << al->rect();
	}
}

void OcularView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
	QAbstractItemView::dataChanged(topLeft, bottomRight);
	int chart_id = 0;
	for (int row = 0; row < model()->rowCount(rootIndex()); ++row) {
		QModelIndex index = model()->index(row, chart_id, rootIndex());
		BodyProps props = model()->data(index).value<BodyProps>();
		AstroLabel* label = labels_->find_by_chart_id(chart_id, props.id);
		bool need_insert = !label;
		if (!label)
			label = LabelFactory::construct(this, chart_id, props);
		label->setProps(props);
		label->setChartId(chart_id);
		if (need_insert) {
			std::pair<AlcIter, bool> result = labels_->insert(label);
			assert (result.second);
		}
	}
}

void OcularView::drawPlanetLines(QPainter* painter)
{
	painter->save();
	double zouter = dimensions_[ODIM_zodiac5dgrR];
	double zinner = dimensions_[ODIM_innerPlanetLabelR];
	double rzinner = dimensions_[ODIM_planetFontSize];
//	painter->setLineWidth(1);
	QPointF pt[2];

	QString strDegree;
	QFont* dgrFont = GlyphManager::get_const_instance().font(dimensions_[ODIM_degreeFontSize], FF_ASTRO);

	BOOST_FOREACH (AstroLabel* al, *labels_) {
		if (al->type() == TYPE_PLANET && al->visible()) {
			painter->setPen(colors_.planetTickColor);
			double ang = al->angle() + dimensions_[ODIM_zeroAngle];
			double angv = al->visibleAngle() + dimensions_[ODIM_zeroAngle];
			double planet_r = al->rect().width() / 2;
			pt[0] = DrawHelper::getXYdeg(ang, zouter);
			pt[1] = DrawHelper::getXYdeg(angv, zinner);
			double dx = pt[1].x() - pt[0].x(), dy = pt[0].y() - pt[1].y();
			double ang0 = atan(dy / dx);
			if (dx < 0)
				ang0 += DrawHelper::PI;
			double hyp = sqrt(dx * dx + dy * dy) - planet_r;
			pt[1].setX(pt[0].x() + cos(ang0) * hyp);
			pt[1].setY(pt[0].y() - sin(ang0) * hyp);
			painter->drawLines(pt, 2);

			painter->setPen(Qt::black);
			painter->setFont(*dgrFont);
			strDegree.sprintf("%02d%c", ((int)al->angle() % DEG_PER_SIGN) + 1, GlyphManager::get_const_instance().degreeSign(FF_ASTRO));
			pt[1] = DrawHelper::getXYdeg(angv, zinner - al->rect().height());
			painter->drawText(pt[1].x(), pt[1].y(), strDegree);
			if (al->flags() & af_Retrograde) {
				strDegree = ">";
				pt[1] = DrawHelper::getXYdeg(angv, zinner - 2 * al->rect().height());
				painter->drawText(pt[1].x(), pt[1].y(), strDegree); // retrograde
			}
		}
	}
	painter->restore();
}

void OcularView::drawHouseLines(QPainter* painter)
{
	painter->save();
	double zinner = dimensions_[ODIM_zodiacInner2R];
//	painter->setLineWidth(1);
//	painter->setBackground(getBackColor());
	QPointF pt[2];

	QString strDegree;
	QFont* dgrFont = GlyphManager::get_const_instance().font(dimensions_[ODIM_degreeFontSize], FF_ASTRO);

	BOOST_FOREACH (AstroLabel* al, *labels_) {
		if (al->type() == TYPE_HOUSE) {
			double ang = al->angle() + dimensions_[ODIM_zeroAngle];
			astro_flag_t af = (astro_flag_t)al->flags();
			pt[0] = DrawHelper::getXYdeg(ang, zinner);
			if (af == af_Undef) {
				pt[1] = DrawHelper::getXYdeg(ang, dimensions_[ODIM_zodiac5dgrR]);
				painter->setPen(colors_.planetTickColor);
				painter->drawLines(pt, 2);
			}
			else {
				painter->setPen(colors_.arrowColor);
				switch (af) {
					case af_Asc:
					case af_MC: {
						double r_ascmc = dimensions_[ODIM_ascArrowR];
						pt[1] = DrawHelper::getXYdeg(ang, r_ascmc);
						painter->drawLines(pt, 2);
						pt[0] = DrawHelper::getXYdeg(ang - 1, r_ascmc * 0.98);
						painter->drawLines(pt, 2);
						pt[0] = DrawHelper::getXYdeg(ang + 1, r_ascmc * 0.98);
						painter->drawLines(pt, 2);
						painter->setPen(Qt::black);
						painter->setFont(*dgrFont);
						if (af == af_Asc) {
							pt[1] = DrawHelper::getXYdeg(ang, r_ascmc * 0.98);
							strDegree.sprintf("%02d%c",
								(int)al->angle() % DEG_PER_SIGN + 1,
								GlyphManager::get_const_instance().degreeSign(FF_ASTRO));
							painter->drawText(pt[1].x(), pt[1].y() - 1, strDegree);
							strDegree.sprintf("%02d'",
								(int)(al->angle() - (int)al->angle()) * 60 + 1);
//							int th = dgrFont->getTextHeight(strDegree);
							painter->drawText(pt[1].x(), pt[1].y(), strDegree);
						}
						else {
							pt[1] = DrawHelper::getXYdeg(ang, r_ascmc * 0.96);
							strDegree.sprintf("%02d%c%02d'",
								(int)al->angle() % DEG_PER_SIGN + 1,
								GlyphManager::get_const_instance().degreeSign(FF_ASTRO),
								(int)(al->angle() - (int)al->angle()) * 60 + 1);
//							int tw = dgrFont->getTextWidth(strDegree);
//							int th = dgrFont->getTextHeight(strDegree);
							painter->drawText(pt[1].x(), pt[1].y(), strDegree);
						}
						}
						break;
					case af_Dsc: {
						double r_dsc = dimensions_[ODIM_ascArrowR] * 0.93;
						double r_circle = dimensions_[ODIM_ascArrowR] * 0.015;
						pt[1] = DrawHelper::getXYdeg(ang, r_dsc);
						painter->drawLines(pt, 2);
						pt[1] = DrawHelper::getXYdeg(ang, r_dsc + r_circle);
						painter->drawEllipse(pt[1].x() - r_circle, pt[1].y() - r_circle, 2 * r_circle, 2 * r_circle); }
						break;
					case af_IC: {
						double r_ic = dimensions_[ODIM_ascArrowR] * 0.96;
						pt[1] = DrawHelper::getXYdeg(ang, r_ic);
						painter->drawLines(pt, 2);
						pt[0] = DrawHelper::getXYdeg(ang + 2, r_ic);
						pt[1] = DrawHelper::getXYdeg(ang - 2, r_ic);
						painter->drawLines(pt, 2); }
						break;
				}
			}
		}
	}
	painter->restore();
}
