#ifndef ASPECTARIUM_H
#define ASPECTARIUM_H

#include <QTableView>

class Aspectarium : public QTableView
{
    Q_OBJECT
public:
	explicit Aspectarium(QWidget *parent, QAbstractItemModel* model);

signals:

public slots:

};

#endif // ASPECTARIUM_H
