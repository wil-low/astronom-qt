#include "CoordValidator.h"
#include <QDebug>

CoordValidator::CoordValidator(QObject *parent, DMS::coord_t coord_type)
: QValidator(parent)
, coord_type_(coord_type)
{
}

QValidator::State CoordValidator::validate (QString& input, int& pos) const
{
	//qDebug() << "validate:" << input << pos;
	return QValidator::Acceptable;
}
