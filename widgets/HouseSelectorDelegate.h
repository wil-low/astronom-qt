#ifndef HouseSelectorDELEGATE_H
#define HouseSelectorDELEGATE_H

#include <QStyledItemDelegate>

class HouseSelectorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
	explicit HouseSelectorDelegate(QObject *parent, int degree_mode, int fontSize);
	void paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option,
				const QModelIndex &index) const;
signals:

public slots:

private:
	int degree_mode_;
	int fontSize_;

};

#endif // HouseSelectorDELEGATE_H
