#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include "TimeLoc.h"
#include "constants.h"
#include <QObject>

class QAction;
class QAbstractItemModel;
class QItemSelectionModel;

class DocumentManager : public QObject
{
	Q_OBJECT
public:
	explicit DocumentManager(QWidget *parent = 0);
	virtual ~DocumentManager();

	void setTimeLoc(int chart_index);
	void changeMode(doc_mode_t type);
	void changeHouseMethod(const QString& method);

signals:
	void reconfigure();
	void timeloc_changed();
	void updateCentralView();

private:
	void setupModel();

	QWidget* parent_;
	QAbstractItemModel *model_;
	QItemSelectionModel *selectionModel;
	TimeLoc timeLoc[MAX_CHART_COUNT];

private slots:
	//void centralViewMenuTriggered(QAction*);
	void houseMenuTriggered(QAction*);
	//void updateViews();
	//void timeloc_set(const TimeLoc&);
	void centralViewAboutToChange(int index);
};

#endif // DOCUMENTMANAGER_H
