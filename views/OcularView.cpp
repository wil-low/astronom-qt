#include "OcularView.h"
#include "../utils/DrawHelper.h"
#include "../utils/constants.h"
#include "../utils/Aspect.h"
#include "../labels/AstroLabelContainer.h"
#include "../labels/LabelFactory.h"
#include "../utils/SettingsManager.h"
#include "../CircleSpread/CircleSpread.h"
#include <QMessageBox>
#include <QSettings>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <boost/foreach.hpp>

OcularView::OcularView(QWidget *parent)
: CentralView(parent, doc_Ocular)
, cursorMode_(cm_None)
, mousePressed_(false)
{
	setSelectionMode(QAbstractItemView::SingleSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setMouseTracking(true);

	BodyProps props;
	props.type = TYPE_ZODIAC;
	for (int i = 0; i < ZODIAC_SIGN_COUNT; ++i) {
		props.id = i;
		labels_->insert(LabelFactory::construct(this, -1, props));
	}
	centerPoint_ = QPointF(viewport()->width() / 2, viewport()->height() / 2);
}

void OcularView::reconfigure()
{
    zeroPoint_ = ZERO_ARIES;//ZERO_ASC;

	BOOST_FOREACH (AstroLabel* label, *labels_) {
		qDebug() << label->toString();
	}
	switch (zeroPoint_) {
		case ZERO_ASC:
		{
			AstroLabel* label = labels_->find_by_chart_id(0, HOUSE_ID_FIRST);
			assert (label && "No Asc label found to set zero point");
			zeroAngle_ = 180 - label->angle();
		}
			break;
		case ZERO_ARIES:
			zeroAngle_ = 180;
			break;
	}
	recalcDimensions(radius_);
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
	painter.translate(centerPoint_);
	if (dimensions_[ODIM_ascArrowR] != 0) {
		painter.setPen(colors_.outerRColor);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_ascArrowR]);
	}

	qreal ang = zeroAngle_;
	qreal delta_ang = DEG_PER_SIGN;

	if (dimensions_[ODIM_zodiacOuterR] != 0) {
		painter.setPen(colors_.outerRColor);
		painter.setBrush(QBrush(colors_.ocularColor));
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_zodiacOuterR]);
		ang = zeroAngle_;
		delta_ang = DEG_PER_SIGN;
		painter.setBrush(colors_.fillColor);
		for (int sign = 0; sign < 6; ++sign) {
			DrawHelper::drawPie(&painter, dimensions_[ODIM_zodiacOuterR], ang + delta_ang, delta_ang);
			ang += delta_ang * 2;
		}
	}

	if (dimensions_[ODIM_zodiac10dgrR] != 0) {
		painter.setPen(colors_.mainLineColor);
		painter.setBrush(colors_.ocularColor);
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
		ang = zeroAngle_;
		delta_ang = DEG_PER_SIGN;
		painter.setPen(Qt::transparent);
		painter.setBrush(colors_.fillColor);
		for (int sign = 0; sign < 6; ++sign) {
			DrawHelper::drawPie(&painter, dimensions_[ODIM_zodiacInner2R], ang + delta_ang, delta_ang);
			ang += delta_ang * 2;
		}
		painter.setPen(colors_.mainLineColor);
		painter.setBrush(Qt::transparent);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_zodiacInner2R]);
	}

	if (dimensions_[ODIM_zodiacInnerR] != 0) {
		painter.setPen(colors_.mainLineColor);
		painter.setBrush(colors_.ocularColor);
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
	ang = zeroAngle_;
	QPointF pt[3];
	pt[0] = DrawHelper::getXYdeg(ang - 1, r_aries * 1.02);
	pt[1] = DrawHelper::getXYdeg(zeroAngle_, r_aries);
	pt[2] = DrawHelper::getXYdeg(ang + 1, r_aries * 1.02);
	painter.drawPolyline(pt, 3);

	ang = zeroAngle_;
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
	ang = zeroAngle_;
	delta_ang = 10;
	zinner = dimensions_[ODIM_zodiac10dgrR];
	zouter = dimensions_[ODIM_zodiacOuterR];
	for (int tick = 0; tick < 360 / 10; ++tick) {
		pt[0] = DrawHelper::getXYdeg(ang, zinner);
		pt[1] = DrawHelper::getXYdeg(ang, zouter);
		painter.drawLines(pt, 1);
		ang += delta_ang;
	}
	if (dimensions_[ODIM_centerGripR] != 0) {
		painter.setPen(colors_.centerGripColor);
		painter.setBrush(Qt::transparent);
		DrawHelper::drawCircle(&painter, dimensions_[ODIM_centerGripR]);
	}

	drawLabels(&painter);
	drawAspects(&painter);
	drawPlanetLines (&painter);
	drawHouseLines (&painter);
}

QModelIndex OcularView::indexAt(const QPoint &point) const
{
	AstroLabel* cur_al = labels_->labelAt(translatePoint(point));
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

bool OcularView::isIndexHidden(const QModelIndex &index) const
{
	AstroLabel* label = findByIndex(index);
	if (label)
		return !label->visible();
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
			qreal width = (*it)->rect().width() / 2;
			if (delta_width < width)
				delta_width = width;
//			FXTRACE((90, "%s\n", (*it)->toString().text()));
		}
		++it;
	}
	delta_width *= 1.2;
	qreal delta_ang = atan (delta_width / r) / DTOR * 2;
	CircleSpread cspread(input);

	std::vector<SpreadValue> output;
	cspread.spread(output, delta_ang, 360);

	BOOST_FOREACH (SpreadValue& sv, output) {
		AstroLabel* label = static_cast<AstroLabel*>(sv.ptr_);
		label->setVisibleAngle(sv.val_);
		//qDebug() << label->toString();
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
		al->setFont(SettingsManager::get_const_instance().font(font_size, FF_ASTRO));
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
		pt = DrawHelper::getXYdeg(zeroAngle_ + al->visibleAngle(), rad[al->type()]);
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

void OcularView::drawPlanetLines(QPainter* painter)
{
	painter->save();
	double zouter = dimensions_[ODIM_zodiac5dgrR];
	double zinner = dimensions_[ODIM_innerPlanetLabelR];
	double zdegree = dimensions_[ODIM_innerPlanetDegreeLabelR];
	double zretro = dimensions_[ODIM_innerPlanetRetrogradeLabelR];
//	painter->setLineWidth(1);
	QPointF pt[2];

	QString strDegree;
	QFont* dgrFont = SettingsManager::get_const_instance().font(dimensions_[ODIM_degreeFontSize], FF_ASTRO);

	BOOST_FOREACH (AstroLabel* al, *labels_) {
		if (al->type() == TYPE_PLANET && al->visible()) {
			painter->setPen(colors_.planetTickColor);
			double ang = al->angle() + zeroAngle_;
			double angv = al->visibleAngle() + zeroAngle_;
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
			painter->drawLines(pt, 1);

			painter->setPen(Qt::black);
			painter->setFont(*dgrFont);
            int degreePart = ((int)al->angle() % DEG_PER_SIGN) + 1;
            QChar degreeSign = SettingsManager::get_const_instance().degreeSign(FF_ASTRO);

            QString strDegree = QString("%1%2")
                .arg(degreePart, 2, 10, QLatin1Char('0'))
                .arg(degreeSign);
			pt[1] = DrawHelper::getXYdeg(angv, zdegree);
			DrawHelper::drawCenteredText(painter, pt[1], strDegree);
			if (al->flags() & af_Retrograde) {
				strDegree = ">";
				pt[1] = DrawHelper::getXYdeg(angv, zretro);
				DrawHelper::drawCenteredText(painter, pt[1], strDegree); // retrograde
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
	QFont* dgrFont = SettingsManager::get_const_instance().font(dimensions_[ODIM_degreeFontSize], FF_ASTRO);
//	qDebug() << __FUNCTION__;
	BOOST_FOREACH (AstroLabel* al, *labels_) {
		if (al->type() == TYPE_HOUSE && al->id() >= HOUSE_ID_FIRST) {
			//qDebug() << al->id() << " flags " << al->flags();
			double ang = al->angle() + zeroAngle_;
			astro_flag_t af = (astro_flag_t)al->flags();
			pt[0] = DrawHelper::getXYdeg(ang, zinner);
			if (af == af_Undef) {
				pt[1] = DrawHelper::getXYdeg(ang, dimensions_[ODIM_zodiac5dgrR]);
				painter->setPen(colors_.planetTickColor);
				painter->drawLines(pt, 1);
			}
			else {
				painter->setPen(colors_.arrowColor);
				switch (af) {
					case af_Asc:
					case af_MC: {
						double r_ascmc = dimensions_[ODIM_ascArrowR];
						pt[1] = DrawHelper::getXYdeg(ang, r_ascmc);
						painter->drawLines(pt, 1);
						pt[0] = DrawHelper::getXYdeg(ang - 1, r_ascmc * 0.98);
						painter->drawLines(pt, 1);
						pt[0] = DrawHelper::getXYdeg(ang + 1, r_ascmc * 0.98);
						painter->drawLines(pt, 1);
						painter->setPen(Qt::black);
						painter->setFont(*dgrFont);
                        if (af == af_Asc) {
                            pt[1] = DrawHelper::getXYdeg(ang, r_ascmc * 0.98);
                            QRectF rect(pt[1], pt[1]);

                            int degPart = ((int)al->angle() % DEG_PER_SIGN) + 1;
                            QChar degreeSign = SettingsManager::get_const_instance().degreeSign(FF_ASTRO);
                            int minPart = (int)((al->angle() - (int)al->angle()) * 60) + 1;

                            QString strDegree = QString("%1%2")
                                .arg(degPart, 2, 10, QLatin1Char('0'))
                                .arg(degreeSign);
                            painter->drawText(rect, Qt::AlignBottom | Qt::TextDontClip, strDegree);

                            strDegree = QString("%1'")
                                .arg(minPart, 2, 10, QLatin1Char('0'));
                            painter->drawText(rect, Qt::AlignTop | Qt::TextDontClip, strDegree);
                        }
                        else {
                            pt[1] = DrawHelper::getXYdeg(ang, r_ascmc * 0.96);
                            QRectF rect(pt[1], pt[1]);

                            int degPart = ((int)al->angle() % DEG_PER_SIGN) + 1;
                            QChar degreeSign = SettingsManager::get_const_instance().degreeSign(FF_ASTRO);
                            int minPart = (int)((al->angle() - (int)al->angle()) * 60) + 1;

                            QString strDegree = QString("%1%2%3'")
                                .arg(degPart, 2, 10, QLatin1Char('0'))
                                .arg(degreeSign)
                                .arg(minPart, 2, 10, QLatin1Char('0'));
                            painter->drawText(rect, Qt::AlignHCenter | Qt::TextDontClip, strDegree);
                        }
						}
						break;
					case af_Dsc: {
						double r_dsc = dimensions_[ODIM_ascArrowR] * 0.93;
						double r_circle = dimensions_[ODIM_ascArrowR] * 0.015;
						pt[1] = DrawHelper::getXYdeg(ang, r_dsc);
						painter->drawLines(pt, 1);
						pt[1] = DrawHelper::getXYdeg(ang, r_dsc + r_circle);
						painter->drawEllipse(pt[1].x() - r_circle, pt[1].y() - r_circle, 2 * r_circle, 2 * r_circle); }
						break;
					case af_IC: {
						double r_ic = dimensions_[ODIM_ascArrowR] * 0.96;
						pt[1] = DrawHelper::getXYdeg(ang, r_ic);
						painter->drawLines(pt, 1);
						pt[0] = DrawHelper::getXYdeg(ang + 2, r_ic);
						pt[1] = DrawHelper::getXYdeg(ang - 2, r_ic);
						painter->drawLines(pt, 1);
					}
						break;
				}
			}
		}
	}
	//qDebug() << "end " <<__FUNCTION__;
	painter->restore();
}

void OcularView::currentChanged (const QModelIndex & current, const QModelIndex & previous)
{
	AstroLabel* label = findByIndex(previous);
	if (label)
		label->setSelected(false);
	label = findByIndex(current);
	if (label)
		label->setSelected(true);
	viewport()->update();
}

void OcularView::invalidateView()
{
	reorderLabels();
	viewport()->update();
}

void OcularView::drawAspects(QPainter* painter)
{
	painter->save();
	QPen pen(colors_.aspectTickColor);
	pen.setWidth(2);
	painter->setPen(pen);
	QPointF pt[2];
	BOOST_FOREACH (AstroLabel* al, *labels_) {
		if (al->type() == TYPE_PLANET) {
			double ang = al->angle() + zeroAngle_;
			pt[0] = DrawHelper::getXYdeg(ang, dimensions_[ODIM_zodiacInnerR]);
			pt[1] = DrawHelper::getXYdeg(ang, dimensions_[ODIM_aspectR]);
			painter->drawLines(pt, 1);
		}
	}

	pen.setWidth(1);
	painter->setPen(pen);
	Aspect aspect;
	for (int row = 0; row < aspectModel_->rowCount(); ++row) {
		QModelIndex index = aspectModel_->index(row, 0);
		if (index.data(Qt::VisibilityRole).toBool()) {
			aspect = aspectModel_->data(index).value<Aspect>();
			AstroLabel* al[2];
			bool isVisible = true;
			for (int idx = 0; idx < 2; ++idx) {
				al[idx] = labels_->find_by_chart_id(aspect.body_[idx].chart_, aspect.body_[idx].id_);
				if (al[idx]->visible())
					pt[idx] = DrawHelper::getXYdeg(al[idx]->angle() + zeroAngle_, dimensions_[ODIM_aspectR]);
				else
					isVisible = false;
			}
			if (isVisible)
				painter->drawLines(pt, 1);
		}
	}
	painter->restore();
}

QPoint OcularView::translatePoint(const QPoint& p) const
{
	return QPoint(p.x() - centerPoint_.x(), p.y() - centerPoint_.y());
}

bool OcularView::viewportEvent (QEvent* event)
{
	const int RESIZE_PRECISION = 2;
	const int MIN_RADIUS = 88;
	if (event->type() == QEvent::MouseMove) {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
		QPoint pos = mouseEvent->pos();
		if (!viewport()->rect().contains(pos)) {
			return true;
		}
		if (!mousePressed_) {
            qreal distance = DrawHelper::distance(centerPoint_, mouseEvent->localPos());
			if (distance < dimensions_[ODIM_centerGripR]) {
				setCursor(QCursor(Qt::OpenHandCursor));
				cursorMode_ = cm_Pan;
			}
			else if (fabs(distance - dimensions_[ODIM_ascArrowR]) < RESIZE_PRECISION) {
				setCursor(QCursor(Qt::CrossCursor));
				cursorMode_ = cm_Resize;
			}
			else {
				setCursor(QCursor(Qt::ArrowCursor));
				cursorMode_ = cm_None;
			}
		}
		else if (cursorMode_ == cm_Pan) {
            centerPoint_ = mouseEvent->localPos();
			viewport()->update();
		}
		else if (cursorMode_ == cm_Resize) {
            qreal r = DrawHelper::distance(centerPoint_, mouseEvent->localPos());
			if (r > MIN_RADIUS) {
				radius_ = r;
				recalcDimensions(radius_);
			}
		}
		return true;
	}
	else if (cursorMode_ != cm_None) {
		if (event->type() == QEvent::MouseButtonPress) {
			mousePressed_ = true;
		}
		else if (event->type() == QEvent::MouseButtonRelease) {
			if (mousePressed_) {
				setCursor(QCursor(Qt::ArrowCursor));
				cursorMode_ = cm_None;
				viewport()->update();
			}
			mousePressed_ = false;
			return true;
		}
	}
	return CentralView::viewportEvent(event);
}

void OcularView::restoreState(QSettings& settings)
{
	radius_ = settings.value("radius", 377).toInt();
	centerPoint_ = settings.value("center", QPointF(100, 100)).value<QPointF>();

	settings.beginGroup("dimensions");
	defaultDimensions_[ODIM_radius] = settings.value("radius", 377).toInt();
	defaultDimensions_[ODIM_ascArrowR] = settings.value("ascArrowR", 374).toInt();
	defaultDimensions_[ODIM_zodiacOuterR] = settings.value("zodiacOuterR", 300).toInt();
	defaultDimensions_[ODIM_zodiac10dgrR] = settings.value("zodiac10dgrR", 291).toInt();
	defaultDimensions_[ODIM_zodiac5dgrR] = settings.value("zodiac5dgrR", 262).toInt();
	defaultDimensions_[ODIM_innerPlanetLabelR] = settings.value("innerPlanetLabelR", 234).toInt();
	defaultDimensions_[ODIM_innerPlanetDegreeLabelR] = settings.value("innerPlanetDegreeLabelR", 212).toInt();
	defaultDimensions_[ODIM_innerPlanetRetrogradeLabelR] = settings.value("innerPlanetRetrogradeLabelR", 195).toInt();
	defaultDimensions_[ODIM_zodiac30dgrR] = settings.value("zodiac30dgrR", 0).toInt();
	defaultDimensions_[ODIM_innerPlanetR] = settings.value("innerPlanetR", 248).toInt();
	defaultDimensions_[ODIM_zodiacInner2R] = settings.value("zodiacInner2R", 147).toInt();
	defaultDimensions_[ODIM_zodiacInnerR] = settings.value("zodiacInnerR", 141).toInt();
	defaultDimensions_[ODIM_aspectR] = settings.value("aspectR", 138).toInt();
	defaultDimensions_[ODIM_planetFontSize] = settings.value("planetFontSize", 5).toInt();
	defaultDimensions_[ODIM_zodiacFontSize] = settings.value("zodiacFontSize", 4).toInt();
	defaultDimensions_[ODIM_degreeFontSize] = settings.value("degreeFontSize", 3).toInt();
	defaultDimensions_[ODIM_tick10Size] = settings.value("tick10Size", 8).toInt();
	defaultDimensions_[ODIM_tick5Size] = settings.value("tick5Size", 5).toInt();
	defaultDimensions_[ODIM_centerGripR] = settings.value("centerGripR", 5).toInt();
	settings.endGroup();

	settings.beginGroup("colors");
	colorScheme_ = settings.value("colorScheme", "default").toString();
	settings.beginGroup(colorScheme_);
	colors_.outerRColor = settings.value("outerRColor", QColor(129,135,187/*78,84,136*/)).value<QColor>(); // almost grey
	colors_.ocularColor = settings.value("ocularColor", QColor(255,255,255)).value<QColor>(); // white
	colors_.contourColor = settings.value("contourColor", QColor(0,0,0)).value<QColor>(); // light violet
	colors_.mainLineColor = settings.value("mainLineColor", QColor(128,0,192)).value<QColor>();
	colors_.labelColor = settings.value("labelColor", QColor(0,0,0)).value<QColor>();
	colors_.fillColor = settings.value("fillColor", QColor(240,224,255)).value<QColor>();
	colors_.arrowColor = settings.value("arrowColor", QColor(255,0,0)).value<QColor>();
	colors_.cuspidColor = settings.value("cuspidColor", QColor(0,192,128)).value<QColor>();
	colors_.tick10Color = settings.value("tick10Color", QColor(192,0,255)).value<QColor>();
	colors_.innerRColor = settings.value("innerRColor", QColor(192,0,255)).value<QColor>();
	colors_.planetTickColor = settings.value("planetTickColor", QColor(0,192,255)).value<QColor>();
	colors_.aspectTickColor = settings.value("aspectTickColor", QColor(0,0,0)).value<QColor>();
	colors_.centerGripColor = settings.value("centerGripColor", QColor(129,135,187)).value<QColor>(); // almost grey
	settings.endGroup();
	settings.endGroup();
}

void OcularView::saveState(QSettings& settings)
{
	settings.setValue("radius", radius_);
	settings.setValue("center", centerPoint_);

/*
	settings.beginGroup("ocular:dimensions");
	defaultDimensions_[ODIM_radius] = settings.value("radius", 377).toInt();
	defaultDimensions_[ODIM_ascArrowR] = settings.value("ascArrowR", 374).toInt();
	defaultDimensions_[ODIM_zodiacOuterR] = settings.value("zodiacOuterR", 300).toInt();
	defaultDimensions_[ODIM_zodiac10dgrR] = settings.value("zodiac10dgrR", 291).toInt();
	defaultDimensions_[ODIM_zodiac5dgrR] = settings.value("zodiac5dgrR", 262).toInt();
	defaultDimensions_[ODIM_innerPlanetLabelR] = settings.value("innerPlanetLabelR", 234).toInt();
	defaultDimensions_[ODIM_innerPlanetDegreeLabelR] = settings.value("innerPlanetDegreeLabelR", 212).toInt();
	defaultDimensions_[ODIM_innerPlanetRetrogradeLabelR] = settings.value("innerPlanetRetrogradeLabelR", 195).toInt();
	defaultDimensions_[ODIM_zodiac30dgrR] = settings.value("zodiac30dgrR", 0).toInt();
	defaultDimensions_[ODIM_innerPlanetR] = settings.value("innerPlanetR", 248).toInt();
	defaultDimensions_[ODIM_zodiacInner2R] = settings.value("zodiacInner2R", 147).toInt();
	defaultDimensions_[ODIM_zodiacInnerR] = settings.value("zodiacInnerR", 141).toInt();
	defaultDimensions_[ODIM_aspectR] = settings.value("aspectR", 138).toInt();
	defaultDimensions_[ODIM_planetFontSize] = settings.value("planetFontSize", 5).toInt();
	defaultDimensions_[ODIM_zodiacFontSize] = settings.value("zodiacFontSize", 4).toInt();
	defaultDimensions_[ODIM_degreeFontSize] = settings.value("degreeFontSize", 3).toInt();
	defaultDimensions_[ODIM_tick10Size] = settings.value("tick10Size", 8).toInt();
	defaultDimensions_[ODIM_tick5Size] = settings.value("tick5Size", 5).toInt();
	defaultDimensions_[ODIM_centerGripR] = settings.value("centerGripR", 5).toInt();
	settings.endGroup();
*/
	settings.beginGroup("colors");
	settings.setValue("colorScheme", colorScheme_);
	settings.beginGroup(colorScheme_);
	settings.setValue("outerRColor", colors_.outerRColor);
	settings.setValue("ocularColor", colors_.ocularColor);
	settings.setValue("contourColor", colors_.contourColor);
	settings.setValue("mainLineColor", colors_.mainLineColor);
	settings.setValue("labelColor", colors_.labelColor);
	settings.setValue("fillColor", colors_.fillColor);
	settings.setValue("arrowColor", colors_.arrowColor);
	settings.setValue("cuspidColor", colors_.cuspidColor);
	settings.setValue("tick10Color", colors_.tick10Color);
	settings.setValue("innerRColor", colors_.innerRColor);
	settings.setValue("planetTickColor", colors_.planetTickColor);
	settings.setValue("aspectTickColor", colors_.aspectTickColor);
	settings.setValue("centerGripColor", colors_.centerGripColor);
	settings.endGroup();
	settings.endGroup();

}

