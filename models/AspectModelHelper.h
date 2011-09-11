#ifndef ASPECTMODELHELPER_H
#define ASPECTMODELHELPER_H

class QAbstractItemModel;

class AspectModelHelper
{
public:
	AspectModelHelper(QAbstractItemModel* model, bool clear = false);
	void insertAspects(const QAbstractItemModel* source_model,
					   int chart_index0, int chart_index1);

private:
	QAbstractItemModel* model_;
};

#endif // ASPECTMODELHELPER_H
