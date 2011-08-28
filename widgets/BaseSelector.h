#ifndef BaseSelector_H
#define BaseSelector_H

#include <QWidget>

class BaseSelectorDelegate;

class QTabBar;
class QListView;
class QModelIndex;
class QAbstractItemModel;
class QAbstractItemView;
class QSortFilterProxyModel;

class BaseSelector : public QWidget
{
    Q_OBJECT
public:
	explicit BaseSelector(QWidget *parent, QAbstractItemModel* model);
	~BaseSelector();
	void setFilterModels();

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

	virtual BaseSelectorDelegate* getDelegate() = 0;
	void setDelegate(QListView* listView, int fontSize, int property);

	enum model_t {
		MODEL_MAIN = 0,
		MODEL_SECONDARY = 1
	};

	virtual QSortFilterProxyModel* getFilterModel(model_t modelType) = 0;

	void listViewPressed(QListView* listView, const QModelIndex& index);
	int listFontSize_;
	BaseSelectorDelegate* delegate_;

private:

};

#endif // BaseSelector_H
