#include "BodyProps.h"

BodyProps::BodyProps()
: id(-1)
, type(TYPE_LAST)
, userData(0)
, flags(0)
{
	for (int i = 0; i < bp_Last; ++i)
		prop[i] = 0;
}

BodyProps::BodyProps(body_type_t type0, int id0, bool clear)
: id(id0)
, type(type0)
, userData(0)
, flags(0)
{
	if (clear) {
		for (int i = 0; i < bp_Last; ++i)
			prop[i] = 0;
	}
}

double BodyProps::normalize(double val, double circle_limit)
{
	while (val < 0)
		val += circle_limit;
	while (val >= circle_limit)
		val -= circle_limit;
	return val;
}
