#ifndef TIMEOFFSETVALIDATOR_H
#define TIMEOFFSETVALIDATOR_H

#include <QValidator>

class TimeOffsetValidator : public QValidator
{
    Q_OBJECT
public:
    explicit TimeOffsetValidator(QObject *parent = 0);
	virtual State validate (QString& input, int& pos) const;
signals:

public slots:

};

#endif // TIMEOFFSETVALIDATOR_H
