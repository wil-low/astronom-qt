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

}
