#ifndef HouseSelectorDELEGATE_H
#define HouseSelectorDELEGATE_H

#include "BaseSelectorDelegate.h"

class HouseSelectorDelegate : public BaseSelectorDelegate
{
    Q_OBJECT
public:
	explicit HouseSelectorDelegate(QObject *parent);
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const;
signals:

public slots:

private:
};

#endif // HouseSelectorDELEGATE_H
