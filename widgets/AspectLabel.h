#ifndef AspectLabel_H
#define AspectLabel_H

#include <QGraphicsItem>

class AspectLabel : public QGraphicsItem
{
public:
	explicit AspectLabel(QGraphicsItem * parent = 0);
	virtual QRectF boundingRect () const;
	virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
	virtual QPainterPath	shape () const;
	virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
	virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
signals:

public slots:

private:
	QPainterPath *path_;
	QPen* pen_;
};

#endif // AspectLabel_H
