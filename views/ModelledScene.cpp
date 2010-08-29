#include "ModelledScene.h"

ModelledScene::ModelledScene(QObject *parent)
: QGraphicsScene(parent)
, model_(NULL)
{
}

void ModelledScene::setModel(QAbstractItemModel *model)
{
	model_ = model;
}
