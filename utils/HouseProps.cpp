#include "HouseProps.h"

HouseProps::HouseProps()
: method(hp_Undef) 
{
}

int HouseProps::cuspCount() const
{
	if (method == hp_Undef)
		return 0;
	else
		return (method == hp_Gaquelin ? 36 : 12);
}
