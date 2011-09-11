#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include "TimeLoc.h"
#include "constants.h"
#include <QObject>
#include <vector>

class QAction;
class QAbstractItemModel;
class QItemSelectionModel;
class DocumentWidget;
class FormulaForm;

namespace Core {
	namespace Internal {
		class FancyTabWidget;
	}
}

class DocumentManager : public QObject
{
	Q_OBJECT
public:
	explicit DocumentManager(QWidget *parent = 0);
	virtual ~DocumentManager();

	void setTimeLoc(int chart_index, const TimeLoc& tl);
	void changeHouseMethod(const QString& method);
	void setControlledWidget(Core::Internal::FancyTabWidget* w);
	void setMode(doc_mode_t type);
	void saveState();
	void restoreState();
	void setVariables(FormulaForm& form);
signals:
	void reconfigure();
	void timeloc_changed();
	void updateCentralView();
	void setCurrentTab(int tabIndex);

private:
	void setupModel();

	QWidget* parent_;
	QAbstractItemModel *bodyModel_;
	QAbstractItemModel *aspectModel_;
	QItemSelectionModel *selectionModel;
	TimeLoc timeLoc[MAX_CHART_COUNT];
	Core::Internal::FancyTabWidget* tabWidget_;
	std::vector<DocumentWidget*> documents_;

private slots:
	void houseMenuTriggered(QAction*);
	//void updateViews();
	//void timeloc_set(const TimeLoc&);
	void currentAboutToShow(int index);
};

#endif // DOCUMENTMANAGER_H
