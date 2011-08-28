#ifndef BASESELECTORDELEGATE_H
#define BASESELECTORDELEGATE_H

#include <QStyledItemDelegate>

class BaseSelectorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
	explicit BaseSelectorDelegate(QObject *parent);
	void restyle(int degree_mode, int fontSize);
	QSize sizeHint(const QStyleOptionViewItem &option,
				const QModelIndex &index) const;
signals:

public slots:

protected:
	int degree_mode_;
	int fontSize_;

};

#endif // BASESELECTORDELEGATE_H
