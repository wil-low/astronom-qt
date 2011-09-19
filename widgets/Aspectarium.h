#ifndef ASPECTARIUM_H
#define ASPECTARIUM_H

#include <QTableView>

class Aspectarium : public QTableView
{
    Q_OBJECT
public:
	explicit Aspectarium(QWidget *parent, QAbstractItemModel* model);

signals:
	void invalidate();

public slots:
	void tablePressed(const QModelIndex& index);
};

#endif // ASPECTARIUM_H
