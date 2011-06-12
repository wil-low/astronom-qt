#ifndef TABBODYLIST_H
#define TABBODYLIST_H

#include <QTabWidget>
#include "../utils/BodyHolder.h"

class QStandardItemModel;

class TabBodyList : public QTabWidget, public BodyHolder
{
    Q_OBJECT
public:
	explicit TabBodyList(QWidget *parent, QObject* sender);
	virtual void insertPlanet();
	virtual void insertHouse();

signals:

public slots:
private:
	QStandardItemModel* model_;
};

#endif // TABBODYLIST_H
