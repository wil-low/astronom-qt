#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

namespace Ui {
    class MainForm;
}

class QGraphicsScene;
class QGraphicsView;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private:
    Ui::MainForm *ui;
	QGraphicsScene *scene_;
	QGraphicsView *view_;

private slots:
	void on_actionGlyph_manager_activated();
 void on_actionInput_data_activated();
};

#endif // MAINFORM_H
