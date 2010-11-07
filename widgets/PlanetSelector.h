#ifndef PLANETSELECTOR_H
#define PLANETSELECTOR_H

#include <QWidget>

class QTabBar;
class QListView;
class QModelIndex;
class QAbstractItemModel;
class QAbstractItemView;

class PlanetSelector : public QWidget
{
    Q_OBJECT
public:
	explicit PlanetSelector(QWidget *parent, QAbstractItemModel* model);
	~PlanetSelector();
	void copySelectionModel(QAbstractItemView* itemView);
signals:

public slots:
	void tabChanged(int index);
	void listViewPressed(const QModelIndex& index);

private:
	QTabBar* tabBar_;
	QListView* listView_;
	void setDelegate(int fontSize, int property);
	int listFontSize_;
};

#endif // PLANETSELECTOR_H
