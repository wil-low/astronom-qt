#ifndef PLANETSELECTORDELEGATE_H
#define PLANETSELECTORDELEGATE_H

#include <QStyledItemDelegate>

class PlanetSelectorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
	explicit PlanetSelectorDelegate(QObject *parent, int degree_mode, int fontSize);
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

#endif // PLANETSELECTORDELEGATE_H
