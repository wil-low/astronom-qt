#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "../utils/TimeLoc.h"
#include "../utils/constants.h"

namespace Ui {
    class MainForm;
}

class QActionGroup;
class QAction;
class InputForm;
class PersonsForm;
class DocumentManager;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
	virtual ~MainForm();

signals:
	void reconfigure();
	void updateDocument();

private:
	Ui::MainForm *ui;
	InputForm* input_;
	DocumentManager* manager_;
	PersonsForm* persons_;
	void applyInputData();
	void loadHouseMenu();
	void createDockWindows();
	QActionGroup* houseActionGroup_;
	QActionGroup* centralViewActionGroup_;

private slots:
	void on_actionImport_triggered();
	void on_actionPersons_activated();
	void on_actionFormula_activated();
	void on_actionGlyph_manager_activated();
	void on_actionInput_data_activated();
	void timeloc_set(const TimeLoc& tl);
};

#endif // MAINFORM_H
