#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

namespace Ui {
    class MainForm;
}

class QGraphicsScene;
class QGraphicsView;
class InputForm;
class QAbstractItemModel;
class QItemSelectionModel;
class TimeLoc;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
	void setTimeLoc(int chart_index, const TimeLoc & tl);
signals:
	void reconfigure();

private:
    Ui::MainForm *ui;
	QWidget* view_;
	InputForm* input_;
	void setupModel();
	QAbstractItemModel *model_;
	QItemSelectionModel *selectionModel;
private slots:
	void on_doubleSpinBox_valueChanged(double );
	void on_actionGlyph_manager_activated();
	void on_actionInput_data_activated();
};

#endif // MAINFORM_H
