#ifndef INPUTFORM_H
#define INPUTFORM_H

#include <QDialog>

namespace Ui {
    class InputForm;
}

class InputForm : public QDialog
{
    Q_OBJECT

public:
    explicit InputForm(QWidget *parent = 0);
    ~InputForm();

private:
    Ui::InputForm *ui;
};

#endif // INPUTFORM_H
