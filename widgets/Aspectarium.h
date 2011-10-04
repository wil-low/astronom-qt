#ifndef ASPECTARIUM_H
#define ASPECTARIUM_H

#include <QTableView>

class AspectariumProxyModel;
class AspectariumMenu;

class Aspectarium : public QTableView
{
    Q_OBJECT
public:
	explicit Aspectarium(QWidget *parent, QAbstractItemModel* model);

signals:
	void invalidate();

public slots:
	void tablePressed(const QModelIndex& index);

protected:
	virtual void resizeEvent(QResizeEvent* event);

private:
	AspectariumProxyModel* proxyModel_;
    AspectariumMenu* popupMenu_;
};

#endif // ASPECTARIUM_H
