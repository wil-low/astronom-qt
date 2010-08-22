#ifndef ASTROLABEL_H
#define ASTROLABEL_H

#include <QGraphicsSimpleTextItem>

class AstroLabel : public QGraphicsSimpleTextItem
{
public:
	explicit AstroLabel(const QString & text, QGraphicsItem * parent = 0);
	virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
signals:

public slots:

};

#endif // ASTROLABEL_H
