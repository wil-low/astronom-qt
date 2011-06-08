#include "TimeOffsetValidator.h"

TimeOffsetValidator::TimeOffsetValidator(QObject *parent) :
    QValidator(parent)
{
}

QValidator::State TimeOffsetValidator::validate (QString& input, int& pos) const
{
	//qDebug() << "validate:" << input << pos;
	return QValidator::Acceptable;
}
