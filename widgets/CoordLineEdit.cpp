#include "CoordLineEdit.h"
#include "../utils/validators/CoordValidator.h"
#include <QDebug>

CoordLineEdit::CoordLineEdit(QWidget *parent)
: QLineEdit(parent)
, coord_type_(DMS::COORD_UNKNOWN)
{
}

void CoordLineEdit::setCoordType(DMS::coord_t coord_type)
{
	coord_type_ = coord_type;
	if (coord_type_ == DMS::COORD_TZ)
		setInputMask("X00:00:00;_");
	else
		setInputMask("000°00'00\"A;_");
	setValidator(new CoordValidator(this, coord_type_));
}

QString CoordLineEdit::dbText() const
{
	QString txt = displayText();
	QString letter = txt.right(1);
	txt = txt.mid(0, 3) + txt.mid(4, 2) + txt.mid(7, 2);
	txt = ((letter == "N" || letter == "E") ? "+" : "-") + txt;
	return txt;
}
