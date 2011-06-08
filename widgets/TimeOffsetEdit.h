#ifndef TIMEOFFSETEDIT_H
#define TIMEOFFSETEDIT_H

#include <QLineEdit>

class TimeOffsetEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TimeOffsetEdit(QWidget *parent = 0);
	QString dbText() const;
signals:

public slots:
private:
	bool isNegative_;
};

#endif // TIMEOFFSETEDIT_H
