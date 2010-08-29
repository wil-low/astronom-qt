#include "OcularScene.h"
#include <QSettings>
#include <QPainter>
#include <math.h>

#include "../utils/constants.h"

OcularScene::OcularScene(QObject *parent)
: ModelledScene(parent)
, zeroPoint_(ZERO_ARIES)
, zeroAngle_(180)
{
}

void OcularScene::reconfigure()
{
	QSettings settings;
	settings.beginGroup("ocular:dimensions");
	dimensions_.ascArrowR = settings.value("ascArrowR", 374).toInt();
	dimensions_.zodiacOuterR = settings.value("zodiacOuterR", 300).toInt();
	dimensions_.zodiac10dgrR = settings.value("zodiac10dgrR", 291).toInt();
	dimensions_.zodiac5dgrR = settings.value("zodiac5dgrR", 262).toInt();
	dimensions_.innerPlanetLabelR = settings.value("innerPlanetLabelR", 234).toInt();
	dimensions_.zodiac30dgrR = settings.value("zodiac30dgrR", 0).toInt();
	dimensions_.innerPlanetR = settings.value("innerPlanetR", 248).toInt();
	dimensions_.zodiacInner2R = settings.value("zodiacInner2R", 147).toInt();
	dimensions_.zodiacInnerR = settings.value("zodiacInnerR", 141).toInt();
	dimensions_.aspectR = settings.value("aspectR", 374).toInt();
	dimensions_.planetFontSize = settings.value("planetFontSize", 5).toInt();
	dimensions_.zodiacFontSize = settings.value("zodiacFontSize", 4).toInt();
	dimensions_.degreeFontSize = settings.value("degreeFontSize", 3).toInt();
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

	addZodiacSigns();
	reorderItems();
}

void OcularScene::drawCircle(QPainter* painter, qreal radius)
{
	painter->drawEllipse(QPointF(0, 0), radius, radius);
}

void OcularScene::drawArc(QPainter* painter, qreal radius, qreal startAngle, qreal spanAngle)
{
	QRectF rect(-radius, -radius, radius * 2, radius * 2);
	painter->drawArc(rect, startAngle * 16, spanAngle * 16);
}

void OcularScene::drawPie(QPainter* painter, qreal radius, qreal startAngle, qreal spanAngle)
{
	QRectF rect(-radius, -radius, radius * 2, radius * 2);
	painter->drawPie(rect, startAngle * 16, spanAngle * 16);
}

const int TICK_10_SIZE = 8;
const int TICK_5_SIZE = 5;

void OcularScene::drawBackground (QPainter* painter, const QRectF& rect)
{
	painter->save();
//	painter->setRenderHints(QPainter::Antialiasing);
	if (dimensions_.ascArrowR != 0) {
		painter->setPen(colors_.ocularColor);
		drawCircle(painter, dimensions_.ascArrowR);
	}
	qreal ang = zeroAngle_;
	qreal delta_ang = DEG_PER_SIGN;

	if (dimensions_.zodiacOuterR != 0) {
//		if (!is_resizing_) {
			ang = zeroAngle_;
			delta_ang = DEG_PER_SIGN;
			painter->setBrush(colors_.fillColor);
			for (int sign = 0; sign < 6; ++sign) {
				drawPie(painter, dimensions_.zodiacOuterR, ang + delta_ang, delta_ang);
				ang += delta_ang * 2;
			}
//		}
		painter->setPen(colors_.contourColor);
		painter->setBrush(Qt::transparent);
		drawCircle(painter, dimensions_.zodiacOuterR);
	}

	if (dimensions_.zodiac10dgrR != 0) {
		painter->setPen(colors_.mainLineColor);
		painter->setBrush(Qt::white);
		drawCircle(painter, dimensions_.zodiac10dgrR);
	}
	if (dimensions_.zodiac5dgrR != 0) {
		painter->setPen(colors_.mainLineColor);
		drawCircle(painter, dimensions_.zodiac5dgrR);
	}
	if (dimensions_.zodiac30dgrR != 0) {
		painter->setPen(colors_.mainLineColor);
		drawCircle(painter, dimensions_.zodiac30dgrR);
	}
	if (dimensions_.zodiacInner2R != 0) {
//		if (!is_resizing_) {
			ang = zeroAngle_;
			delta_ang = DEG_PER_SIGN;
			painter->setPen(Qt::transparent);
			painter->setBrush(colors_.fillColor);
			for (int sign = 0; sign < 6; ++sign) {
				drawPie(painter, dimensions_.zodiacInner2R, ang + delta_ang, delta_ang);
				ang += delta_ang * 2;
//			}
		}
		painter->setPen(colors_.mainLineColor);
		painter->setBrush(Qt::transparent);
		drawCircle(painter, dimensions_.zodiacInner2R);
	}

	if (dimensions_.zodiacInnerR != 0) {
		painter->setPen(colors_.mainLineColor);
		painter->setBrush(Qt::white);
		drawCircle(painter, dimensions_.zodiacInnerR);
	}
/*
	if (dimensions_.aspectR != 0) {
		painter->setPen(colors_.mainLineColor);
		drawCircle(painter, dimensions_.aspectR);
	}
*/


	painter->setPen(colors_.ocularColor);
	painter->setBrush(Qt::transparent);
	drawCircle(painter, dimensions_.ascArrowR * 0.06);

	// Aries line
	painter->setPen(colors_.arrowColor);

	qreal r_aries = dimensions_.zodiacOuterR + 1;
	ang = zeroAngle_;
	QPointF pt[3];
	pt[0] = getXYdeg(ang - 1, r_aries * 1.02);
	pt[1] = getXYdeg(zeroAngle_, r_aries);
	pt[2] = getXYdeg(ang + 1, r_aries * 1.02);
	painter->drawPolyline(pt, 3);

	ang = zeroAngle_;
	delta_ang = 5;
	qreal zinner = dimensions_.zodiac5dgrR;
	qreal zouter;
	qreal zinner1 = dimensions_.zodiacInnerR;
	qreal zinner2 = dimensions_.zodiacInner2R;

	QPen pen1(colors_.mainLineColor);
	pen1.setWidth(1);
	QPen pen2(colors_.mainLineColor);
	pen2.setWidth(2);
	QPointF pti[2];
	for (int tick = 0; tick < 360 / 5; ++tick) {
		pt[0] = getXYdeg(ang, zinner);
		if (tick % 6 == 0) { // solid line - sign
			painter->setPen(pen1);
			pti[0] = getXYdeg(ang, zinner1);
			pti[1] = getXYdeg(ang, zinner2);
			painter->drawLines(pti, 1);
			painter->setPen(pen2);
			pt[1] = getXYdeg(ang, zinner + TICK_10_SIZE);
		}
		else {
			painter->setPen(pen1);
			pt[1] = getXYdeg(ang, zinner + TICK_5_SIZE);
		}
		painter->drawLines(pt, 1);
		ang += delta_ang;
	}
	painter->setPen(colors_.tick10Color);
	ang = zeroAngle_;
	delta_ang = 10;
	zinner = dimensions_.zodiac10dgrR;
	zouter = dimensions_.zodiacOuterR;
	for (int tick = 0; tick < 360 / 10; ++tick) {
		pt[0] = getXYdeg(ang, zinner);
		pt[1] = getXYdeg(ang, zouter);
		painter->drawLines(pt, 1);
		ang += delta_ang;
	}
/*
	drawAspects(dc);
	drawPlanetLines (dc);
	drawHouseLines (dc);
	drawLabels (dc);*/
	painter->restore();
}


QPointF OcularScene::getXYdeg(qreal degree, qreal len)
{
	return QPointF(len * cos(degree * DTOR), -len * sin(degree * DTOR));
};

void OcularScene::addZodiacSigns()
{
/*	QString label_text;
	for (int i = 0; i < ZODIAC_SIGN_COUNT; ++i) {
		label_text.sprintf("%c", GlyphManager::get_const_instance().getLabel(TYPE_ZODIAC, i));
		ZodiacLabel* label = new ZodiacLabel(i, this, -100, -100, 20, 20);
		label->setId(i, label_text);
//		label->setFont(GlyphManager::get_const_instance().getFont(dimensions_.fontSize));
		labels_.insert(label);
	}
*/
}

void OcularScene::reorderItems()
{

}
