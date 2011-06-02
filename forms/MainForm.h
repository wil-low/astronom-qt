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
class QAbstractItemModel;
class QItemSelectionModel;
class QAbstractScrollArea;

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
	QAbstractScrollArea* view_;
	InputForm* input_;
	void setupModel();
	QAbstractItemModel *model_;
	QItemSelectionModel *selectionModel;
	void loadHouseMenu();
	QActionGroup* houseActionGroup_;
	TimeLoc timeLoc[MAX_CHART_COUNT];
	void applyInputData();

private slots:
	void on_actionFormula_activated();
	void on_actionGlyph_manager_activated();
	void on_actionInput_data_activated();
	void houseMenuTriggered(QAction*);
	void updateViews();
};

#endif // MAINFORM_H
