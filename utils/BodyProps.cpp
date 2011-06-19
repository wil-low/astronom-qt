#include "BodyProps.h"

BodyProps::BodyProps()
: id(-1)
, userData(0)
{
	for (int i = 0; i < bp_Last; ++i)
		prop[i] = 0;
}

double BodyProps::normalize(double val, double circle_limit)
{
	while (val < 0)
		val += circle_limit;
	while (val >= circle_limit)
		val -= circle_limit;
	return val;
}
