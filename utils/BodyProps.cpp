#include "BodyProps.h"

BodyProps::BodyProps()
: id(-1)
{
	for (int i = 0; i < bp_Last; ++i)
		prop[i] = 0;
}
