#ifndef PLANETSELECTORDELEGATE_H
#define PLANETSELECTORDELEGATE_H

#include "BaseSelectorDelegate.h"

class BodySelectorDelegate : public BaseSelectorDelegate
{
    Q_OBJECT
public:
	explicit BodySelectorDelegate(QObject *parent);
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const;
signals:

public slots:
};

#endif // PLANETSELECTORDELEGATE_H
