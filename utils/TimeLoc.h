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
	double data_[TL_LAST];
	int cuspCount() const;
	QString method_;
	QString name_;
	QString location_;
/*
	static void initRex(char date_sep);
	TimeLoc();
	virtual ~TimeLoc();
	void set (timeloc_t idx, QString text, bool recalculate = true);
	void set (timeloc_t idx, double val);
	void setName (const QString& text);
	void setLocation (const QString& text);

	double get (timeloc_t idx) const;
	const QString& getStr (timeloc_t idx);
	const QString& getName () const;
	const QString& getLocation () const;

	void serialize(QString& output);
	void deserialize(const QString& input);
	void asTitle(QString& output);

	static QString formatDate (int y, int m, int d);
	static int scan (timeloc_t idx, const QString &str, int *out);

private:
	double data_[TL_LAST];
	QString str_[TL_LAST];

	static date_fmt_t date_fmt_;
	static char date_sep_;
//	static FXRex rex_[TL_LAST];
	*/
};
Q_DECLARE_METATYPE(TimeLoc)

#endif
