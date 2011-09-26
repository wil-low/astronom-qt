#include "AspectariumProxyModel.h"
#include <QDebug>

AspectariumProxyModel::AspectariumProxyModel(QObject *parent, QAbstractItemModel* model)
: QAbstractProxyModel(parent)
, rowCount_(0)
, columnCount_(0)
{
	setSourceModel(model);
}

AspectariumProxyModel::~AspectariumProxyModel()
{
}

QModelIndex AspectariumProxyModel::index(int row, int column, const QModelIndex& parent) const
{
	int sourceRow = row + column * rowCount_;
	if (sourceRow < sourceModel()->rowCount())
		return createIndex(row, column, sourceRow);
	else
		return QModelIndex();
}

QModelIndex AspectariumProxyModel::parent(const QModelIndex& parent) const
{
	return QModelIndex();
}

int AspectariumProxyModel::rowCount(const QModelIndex&) const
{
	return rowCount_;
}

int AspectariumProxyModel::columnCount(const QModelIndex&) const
{
	return columnCount_;
}

QModelIndex AspectariumProxyModel::mapToSource(const QModelIndex& proxy) const
{
	if (proxy.isValid()) {
		int sourceRow = proxy.row() + proxy.column() * rowCount_;
		if (sourceRow < sourceModel()->rowCount())
			return sourceModel()->index(sourceRow, 0, proxy.parent());
	}
	return QModelIndex();
}

QModelIndex AspectariumProxyModel::mapFromSource(const QModelIndex& source) const
{
	int row = source.row() % rowCount_;
	int column = source.row() / rowCount_;
	return index(row, column, source.parent());
}

void AspectariumProxyModel::setRowCount(int rowCount)
{
	beginResetModel();
	rowCount_ = rowCount;
	if (sourceModel()) {
		columnCount_ = sourceModel()->rowCount() / rowCount_;
		if (sourceModel()->rowCount() % rowCount_)
			++columnCount_;
	}
	//qDebug() << "setRowCount:" << sourceModel()->rowCount() << " - " << rowCount_ << columnCount_;
	endResetModel();
}
