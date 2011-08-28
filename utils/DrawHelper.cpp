#include "DrawHelper.h"
#include "constants.h"
#include <QPainter>
#include <math.h>

namespace DrawHelper
{

void drawCircle(QPainter* painter, qreal radius)
{
	painter->drawEllipse(QPointF(0, 0), radius, radius);
}

void drawArc(QPainter* painter, qreal radius, qreal startAngle, qreal spanAngle)
{
	QRectF rect(-radius, -radius, radius * 2, radius * 2);
	painter->drawArc(rect, startAngle * 16, spanAngle * 16);
}

void drawPie(QPainter* painter, qreal radius, qreal startAngle, qreal spanAngle)
{
	QRectF rect(-radius, -radius, radius * 2, radius * 2);
	painter->drawPie(rect, startAngle * 16, spanAngle * 16);
}

QPointF getXYdeg(qreal degree, qreal len)
{
	return QPointF(len * cos(degree * DTOR), -len * sin(degree * DTOR));
};

void drawCenteredText(QPainter* painter, const QPointF& pt, const QString& str)
{
	QFontMetrics fm = painter->fontMetrics();
	QRectF rect = fm.boundingRect(str);
	painter->drawText(pt.x() - rect.width() / 2, pt.y() + rect.height() / 2, str);
}

qreal distance(const QPointF& p0, const QPointF& p1)
{
	return sqrt (pow((p0.x() - p1.x()), 2) + pow((p0.y() - p1.y()), 2));
}
}
