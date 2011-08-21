#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "../utils/TimeLoc.h"
#include "../utils/constants.h"

namespace Ui {
    class MainForm;
}

class QGraphicsScene;
class QGraphicsView;
class QActionGroup;
class QAction;
class InputForm;
class PersonsForm;
class QAbstractItemModel;
class QItemSelectionModel;
class CentralView;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
	void setTimeLoc(int chart_index);
signals:
	void reconfigure();
	void timeloc_changed();
	void updateCentralView();

private:
        Ui::MainForm *ui;
        CentralView* view_;
	InputForm* input_;
	PersonsForm* persons_;
	void setupModel();
	QAbstractItemModel *model_;
	QItemSelectionModel *selectionModel;
	void loadHouseMenu();
	void loadCentralViewMenu();
	void createDockWindows();
	QActionGroup* houseActionGroup_;
	QActionGroup* centralViewActionGroup_;
	TimeLoc timeLoc[MAX_CHART_COUNT];
	void applyInputData();
	void changeCentralView(central_view_t type);
	void changeHouseMethod(const QString& method);
private slots:
	void on_actionImport_triggered();
	void on_actionPersons_activated();
	void on_actionFormula_activated();
	void on_actionGlyph_manager_activated();
	void on_actionInput_data_activated();
	void centralViewMenuTriggered(QAction*);
	void houseMenuTriggered(QAction*);
	void updateViews();
	void timeloc_set(const TimeLoc&);
	void centralViewAboutToChange(int index);
};

#endif // MAINFORM_H
