#ifndef ASPECTARIUMPROXYPROXYMODEL_H
#define ASPECTARIUMPROXYPROXYMODEL_H

#include <QAbstractProxyModel>

class AspectariumProxyModel : public QAbstractProxyModel
{
public:
	AspectariumProxyModel(QObject* parent, QAbstractItemModel* model);
	virtual ~AspectariumProxyModel();
	virtual QModelIndex index(int, int, const QModelIndex&) const;
	virtual QModelIndex parent(const QModelIndex&) const;
	virtual int rowCount(const QModelIndex&) const;
	virtual int columnCount(const QModelIndex&) const;
	virtual QModelIndex mapToSource(const QModelIndex&) const;
	virtual QModelIndex mapFromSource(const QModelIndex&) const;

	void setRowCount(int rowCount);

protected:
private:
	int rowCount_;
	int columnCount_;
};

#endif // ASPECTARIUMPROXYPROXYMODEL_H
