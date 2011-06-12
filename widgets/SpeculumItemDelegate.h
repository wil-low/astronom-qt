#ifndef SPECULUMITEMDELEGATE_H
#define SPECULUMITEMDELEGATE_H

#include <QStyledItemDelegate>

class SpeculumItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SpeculumItemDelegate(QObject *parent = 0);
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem &option,
								 const QModelIndex &index) const;
signals:

public slots:

};

#endif // SPECULUMITEMDELEGATE_H
