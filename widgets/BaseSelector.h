#ifndef BaseSelector_H
#define BaseSelector_H

#include <QWidget>

class QTabBar;
class QListView;
class QModelIndex;
class QAbstractItemModel;
class QAbstractItemView;

class BaseSelector : public QWidget
{
    Q_OBJECT
public:
	explicit BaseSelector(QWidget *parent, QAbstractItemModel* model);
	~BaseSelector();
signals:
	void invalidateViews();

public slots:
	void tabChanged(int index);
	void listMainPressed(const QModelIndex& index);
	void listSecondaryPressed(const QModelIndex& index);
	virtual void timeloc_changed();

protected:
	QAbstractItemModel* model_;
	QTabBar* tabBar_;
	QListView* listMain_;
	QListView* listSecondary_;
	virtual void setDelegate(QListView* listView, int fontSize, int property) = 0;
	void listViewPressed(QListView* listView, const QModelIndex& index);
	int listFontSize_;
};

#endif // BaseSelector_H
