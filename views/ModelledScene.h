#ifndef MODELLEDSCENE_H
#define MODELLEDSCENE_H

#include <QGraphicsScene>
#include <QAbstractItemModel>

class ModelledScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ModelledScene(QObject *parent = 0);
	void setModel(QAbstractItemModel* model);
signals:

public slots:

protected:
	QAbstractItemModel* model_;
};

#endif // MODELLEDSCENE_H
