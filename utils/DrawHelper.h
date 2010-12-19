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
	static const double PI = 3.1415926;
};
