#include "DraggableGraphicsView.h"
#include <QPoint>
#include <QMouseEvent>
#include <stdio.h>

const int CENTER_DELTA = 5;

DraggableGraphicsView::DraggableGraphicsView(QWidget *parent)
: QGraphicsView(parent)
, isMousePressed_(false)
{
	setMouseTracking(true);
	setDragMode(QGraphicsView::ScrollHandDrag);
}
/*
void DraggableGraphicsView::mousePressEvent(QMouseEvent * event)
{
	isMousePressed_ = true;
	setCursor(QCursor(Qt::ClosedHandCursor));
	QPoint pt = event->globalPos();
	QPointF pt2 = mapToScene(pt);
	qDebug ("%f:%f\n", pt2.x(), pt2.y());
}

void DraggableGraphicsView::mouseMoveEvent(QMouseEvent * event)
{
	QPointF pt = mapToScene(event->pos());
	if (isMousePressed_)
	if (abs(pt.x()) < CENTER_DELTA && abs(pt.y()) < CENTER_DELTA) {
		setCursor(QCursor(Qt::PointingHandCursor));
	}
	else
		setCursor(QCursor(Qt::ArrowCursor));
	QGraphicsView::mouseMoveEvent(event);
}

void DraggableGraphicsView::mouseReleaseEvent(QMouseEvent * event)
{
	isMousePressed_ = false;
	setCursor(QCursor(Qt::ArrowCursor));
}
*/
