#ifndef TIMELOC_H
#define TIMELOC_H

#include <QMetaType>
#include <QString>

enum timeloc_t {
	TL_DATETIME = 0,
	TL_TZ,
	TL_LAT,
	TL_LON,
	TL_ELV,
	TL_LAST, // do not use, always last
};

class TimeLoc
{
public:
	TimeLoc();
	TimeLoc(const QString& name, const QString& dateTime, const QString& timezoneOffset,
					 const QString& location, const QString& latitude, const QString& longitude);
	void clear();
	void recalculate(bool fromString);
	QString toString() const;

	double data_[TL_LAST];
	QString str_[TL_LAST];
	int cuspCount() const;
	QString method_;
	QString name_;
	QString location_;
};
Q_DECLARE_METATYPE(TimeLoc)
QDebug operator<< (QDebug dbg, const TimeLoc& tl);

#endif
