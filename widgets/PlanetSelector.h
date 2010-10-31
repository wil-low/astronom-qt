#ifndef PLANETSELECTOR_H
#define PLANETSELECTOR_H

#include <QWidget>
#include <QAbstractItemModel>

class QTabBar;
class QListView;

class PlanetSelector : public QWidget
{
    Q_OBJECT
public:
	explicit PlanetSelector(QWidget *parent, QAbstractItemModel* model);
	~PlanetSelector();
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
