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
		bp_AspectAngle,
		bp_Last
	};
	BodyProps();
	BodyProps(body_type_t type0, int id0, bool clear = false);
	static double normalize(double val, double circle_limit);
	double prop[bp_Last];
	body_type_t type;
	int id;
	int userData;
	int flags;
};

Q_DECLARE_METATYPE(BodyProps)
#endif // BODYPROPS_H
