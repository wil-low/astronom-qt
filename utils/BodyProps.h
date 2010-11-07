#ifndef BODYPROPS_H
#define BODYPROPS_H
#include <QMetaType>
#include "constants.h"

class BodyProps
{
public:
	enum body_property {
		bp_Lon = 0,
		bp_Lat,
		bp_Dist,
		bp_LonSpeed,
		bp_LatSpeed,
		bp_DistSpeed,
		bp_RectAsc,
		bp_OblAsc,
		bp_Declination,
		bp_Last
	};
	BodyProps();
	double prop[bp_Last];
	body_type_t type;
	int id;
	int userData;
};

Q_DECLARE_METATYPE(BodyProps)
#endif // BODYPROPS_H
