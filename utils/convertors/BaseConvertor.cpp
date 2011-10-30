#include "BaseConvertor.h"

BaseConvertor::BaseConvertor()
: isValid_(false)
, mode_(MODE_UNDEF)
{
}

BaseConvertor::BaseConvertor(convert_mode_t mode)
: isValid_(false)
, mode_(mode)
{
}
