#ifndef SPECULUMVIEW_H
#define SPECULUMVIEW_H

#include <QTableView>

class SpeculumView : public QTableView
{
    Q_OBJECT
public:
    explicit SpeculumView(QWidget *parent = 0);
	virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
signals:

public slots:
	void reconfigure();
};

#endif // SPECULUMVIEW_H
