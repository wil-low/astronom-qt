#include "AspectLabel.h"
#include <QPen>
#include <QFont>
#include <QPainter>

AspectLabel::AspectLabel(QGraphicsItem * parent) :
	QGraphicsItem (parent)
{
	setAcceptHoverEvents(true);
	path_ = new QPainterPath;
	path_->addEllipse(50, 50, 30, 20);
	path_->addText(20, 20, QFont("Astronom", 24), "akjhkjh");
	pen_ = new QPen(QBrush(QColor("black")), 1);
}

void AspectLabel::paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setClipRect(boundingRect());
	painter->setBrush(QBrush(QColor("yellow")));
	painter->setPen(*pen_);
	painter->drawPath(*path_);
	painter->drawLine(0, 30, 30, 50);
}

QPainterPath AspectLabel::shape () const
{
	return *path_;
}

QRectF AspectLabel::boundingRect () const
{
	return QRectF(0, 0, 300, 100);
}

void AspectLabel::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
	pen_->setColor(QColor("red"));
	update();
}

void AspectLabel::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
	pen_->setColor(QColor("black"));
	update();
}
