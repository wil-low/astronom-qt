#pragma once
class QPainter;
#include <QPointF>
namespace DrawHelper
{
	void drawCircle(QPainter* painter, qreal radius);
	void drawArc(QPainter* painter, qreal radius, qreal startAngle, qreal spanAngle);
	void drawPie(QPainter* painter, qreal radius, qreal startAngle, qreal spanAngle);
	QPointF getXYdeg(qreal degree, qreal len);
	void drawCenteredText(QPainter* painter, const QPointF& pt, const QString& str);
	qreal distance(const QPointF& p0, const QPointF& p1);
	static const double PI = 3.1415926;
};
