#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Qt>

/// Multiplier for degrees to radians
const double DTOR=0.0174532925199432957692369077;

/// Multiplier for radians to degrees
const double RTOD=57.295779513082320876798154814;

const double SECONDS_IN_DAY = 60 * 60 * 24;

const int ZODIAC_SIGN_COUNT = 12;
const int DEG_PER_SIGN = 30;
const int LAST_PLANET_ID = 9;
const double DENOMINATOR = 10000.0;

const double STABLESPEED=6./60/60;

const char UNNAMED_DOC[] = "<Celestial>";

const int MAX_CHART_COUNT = 3;

namespace Qt {
	const int VisibilityRole = UserRole + 1;
};

void normAngle(double &a);

enum {
	HOUSE_ID_ASC = 99998,
	HOUSE_ID_MC = 99999,
	HOUSE_ID_FIRST = 100000,
};

enum deg_mode {
	dm_Unknown = -1,
	dm_Absolute = 0,
	dm_Longitude,
	dm_RectAsc,
	dm_OblAsc,
	dm_LatDecl,
};

enum body_type_t {
	TYPE_ZODIAC = 0,
	TYPE_PLANET,
	TYPE_ASTEROID,
	TYPE_HOUSE,
	TYPE_ASPECT,
	TYPE_REFERENCE,
	TYPE_LAST,
};

enum font_face_t {
	FF_ASTRO = 0,
	FF_ARIAL,
};

enum astro_flag_t {
	af_Undef = 0,
	af_Asc = 1,
	af_MC = 2,
	af_Dsc = 3,
	af_IC = 4,
	af_Retrograde = 8,
};

enum central_view_t {
	cv_Ocular = 0,
	cv_Speculum,
	cv_Last,
};

static const char* HOUSE_NAMES[] = {
	"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI"
};

const int FLG_ARABIC = 0x1;

#endif // CONSTANTS_H
