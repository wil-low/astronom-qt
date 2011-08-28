#ifndef OCULARDELEGATE_H
#define OCULARDELEGATE_H

#include <QItemDelegate>

class OcularDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit OcularDelegate(QObject *parent = 0);
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const;
	virtual QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
signals:

public slots:

};

#endif // OCULARDELEGATE_H
