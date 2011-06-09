#ifndef PERSONSFORM_H
#define PERSONSFORM_H

#include <QDialog>

class QModelIndex;
class TimeLoc;

namespace Ui {
    class PersonsForm;
}

class PersonsForm : public QDialog
{
    Q_OBJECT

public:
    explicit PersonsForm(QWidget *parent = 0);
    ~PersonsForm();

signals:
	void timeloc_set(const TimeLoc&);

private:
    Ui::PersonsForm *ui;

private slots:
	void on_lvPersons_doubleClicked(const QModelIndex& index);
};

#endif // PERSONSFORM_H
