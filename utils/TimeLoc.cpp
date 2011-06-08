#include "TimeLoc.h"
#include "Ephemeris.h"
#include "constants.h"
#include "DMS.h"

#include <QDebug>
#include <QDateTime>

TimeLoc::TimeLoc()
{
	clear();
}

void TimeLoc::clear()
{
	name_.clear();
	location_.clear();
	for (int i = TL_DATETIME; i < TL_LAST; ++i) {
		data_[i] = 0;
		str_[i].clear();
	}

}

TimeLoc::TimeLoc(const QString& name, const QString& dateTime, const QString& timezoneOffset,
				 const QString& location, const QString& latitude, const QString& longitude)
{
	clear();
	name_ = name;
	location_ = location;
	str_[TL_DATETIME] = dateTime;
	str_[TL_TZ] = timezoneOffset;
	str_[TL_LAT] = latitude;
	str_[TL_LON] = longitude;
}

int TimeLoc::cuspCount() const
{
	if (method_.isEmpty())
		return 0;
	else
		return (method_ == "G" ? 36 : 12);
}

void TimeLoc::recalculate(bool fromString)
{
	if (fromString) {
		QDateTime dateTime = QDateTime::fromString(str_[TL_DATETIME], Qt::ISODate);
		QDate date(dateTime.date());
		QTime time(dateTime.time());
		data_[TL_DATETIME] = Ephemeris::julday (date.year(), date.month(), date.day(),
													time.hour(), time.minute(), time.second());
		DMS dms;
		dms.fromCoord(str_[TL_LAT], DMS::COORD_LAT);
		data_[TL_LAT] = dms.angle();
		dms.fromCoord(str_[TL_LON], DMS::COORD_LON);
		data_[TL_LON] = dms.angle();
		dms.fromOffset(str_[TL_TZ]);
		data_[TL_TZ] = dms.angle();

		data_[TL_DATETIME] -= data_[TL_TZ];
	}
	else {

	}
}

QDebug operator<< (QDebug dbg, const TimeLoc& tl)
{
	dbg.nospace() << "TimeLoc(" << tl.name_ << ", " << tl.location_ << ", [";
	for (int i = TL_DATETIME; i < TL_LAST; ++i) {
		dbg << tl.data_[i] << ", ";
	}
	dbg << "] [";
	for (int i = TL_DATETIME; i < TL_LAST; ++i) {
		dbg << tl.str_[i] << ", ";
	}
	dbg << "]";
	return dbg.space();
}
