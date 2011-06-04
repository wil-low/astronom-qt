#ifndef PERSONSFORM_H
#define PERSONSFORM_H

#include <QDialog>

namespace Ui {
    class PersonsForm;
}

class PersonsForm : public QDialog
{
    Q_OBJECT

public:
    explicit PersonsForm(QWidget *parent = 0);
    ~PersonsForm();

private:
    Ui::PersonsForm *ui;
};

#endif // PERSONSFORM_H
