#ifndef TIMEOFFSETEDIT_H
#define TIMEOFFSETEDIT_H

#include <QLineEdit>

class TimeOffsetEdit : public QLineEdit
{
    Q_OBJECT
	Q_PROPERTY(QString dbText READ dbText WRITE setDbText STORED false)
public:
    explicit TimeOffsetEdit(QWidget *parent = 0);
	QString dbText() const;
	void setDbText(const QString& text);
signals:

public slots:
private:
	bool isNegative_;
};

#endif // TIMEOFFSETEDIT_H
