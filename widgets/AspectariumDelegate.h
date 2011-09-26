#ifndef ASPECTARIUMDELEGATE_H
#define ASPECTARIUMDELEGATE_H

#include <QStyledItemDelegate>

class AspectariumDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
	explicit AspectariumDelegate(QObject *parent);
	void restyle(int fontSize, int height);
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
	int height() const;
private:
	static const int MARGIN;
	int fontSize_;
	qreal width_[4];
	int height_;
};

#endif // ASPECTARIUMDELEGATE_H
