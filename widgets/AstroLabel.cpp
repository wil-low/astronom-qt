#include "AstroLabel.h"
#include <QFont>
#include <QPen>

AstroLabel::AstroLabel(const QString & text, QGraphicsItem * parent) :
	QGraphicsSimpleTextItem(text, parent)
{
	setAcceptHoverEvents(true);
	setFont(QFont("Astronom", 24));
	setBrush(QBrush(QColor("red")));
}

void AstroLabel::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
	setText(text() + "f");
}
