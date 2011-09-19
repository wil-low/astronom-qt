#ifndef ASPECTARIUMDELEGATE_H
#define ASPECTARIUMDELEGATE_H

#include <QStyledItemDelegate>

class AspectariumDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
	explicit AspectariumDelegate(QObject *parent);
	void restyle(int fontSize);
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const;
private:
	int fontSize_;
	qreal width_[3];
};

#endif // ASPECTARIUMDELEGATE_H
