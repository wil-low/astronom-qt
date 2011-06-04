#include "CoordLineEdit.h"
#include "../utils/validators/CoordValidator.h"

CoordLineEdit::CoordLineEdit(QWidget *parent)
: QLineEdit(parent)
, coord_type_(DMS::COORD_UNKNOWN)
{
}

void CoordLineEdit::setCoordType(DMS::coord_t coord_type)
{
	coord_type_ = coord_type;
	setInputMask("000°00'00\"A;_");
	setValidator(new CoordValidator(this, coord_type_));
}
