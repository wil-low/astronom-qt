#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

namespace Ui {
    class MainForm;
}

class QGraphicsScene;
class QGraphicsView;
class InputForm;
class PlanetModel;
class ModelledScene;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

signals:
	void reconfigure();

private:
    Ui::MainForm *ui;
	ModelledScene* scene_;
	QGraphicsView *view_;
	InputForm* input_;
	PlanetModel* model_;

private slots:
	void on_doubleSpinBox_valueChanged(double );
	void on_actionGlyph_manager_activated();
	void on_actionInput_data_activated();
};

#endif // MAINFORM_H
