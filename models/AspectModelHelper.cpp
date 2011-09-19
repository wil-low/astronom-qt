#include "AspectModelHelper.h"
#include "../utils/BodyProps.h"
#include "../utils/Aspect.h"
#include "../utils/AspectManager.h"
#include <QAbstractItemModel>
#include <QDebug>

AspectModelHelper::AspectModelHelper(QAbstractItemModel* model, bool clear)
: model_(model)
{
	if (clear)
		model_->removeRows(0, model_->rowCount(QModelIndex()), QModelIndex());
}

void AspectModelHelper::insertAspects(const QAbstractItemModel* source_model,
								int chart_index0, int chart_index1)
{
	Aspect aspect;
	BodyProps body0, body1;
	int row_count = source_model->rowCount();
	for (int row0 = 0; row0 < row_count; ++row0) {
		for (int row1 = (chart_index0 == chart_index1) ? row0 + 1 : 0; row1 < row_count; ++row1) {
			// do not compare with itself
			if (row0 == row1)
				continue;
			QModelIndex index = source_model->index(row0, chart_index0);
			body0 = source_model->data(index).value<BodyProps>();
			index = source_model->index(row1, chart_index1);
			body1 = source_model->data(index).value<BodyProps>();
			if (body0.type == TYPE_PLANET && body1.type == TYPE_PLANET) {
				if (AspectManager::get_const_instance().makeAspect(
						aspect, chart_index0, body0, chart_index1, body1)) {
					qDebug() << "makeAspect " << body0.id << ", " << body1.id;
					int row = model_->rowCount();
					model_->insertRows(row, 1, QModelIndex());
					index = model_->index(row, 0, QModelIndex());
					model_->setData (index, qVariantFromValue(aspect));
					model_->setData (index, true, Qt::VisibilityRole);
				}
			}
		}
	}
}
