#pragma once

#include <QString>

class DMS 
{
public:
	DMS();
	DMS (double angle);
	DMS (const QString& dddmmss);
	void calculate (double angle);
	void calculate (const QString& dddmmss);
	QString toMaskedString() const;
	int deg() const;
	int min() const;
	int sec() const;
	int zodiac() const;
	int zod_deg() const;
	double angle() const;
private:
	int deg_, min_, sec_;
	int zodiac_;
	int zod_deg_;
	double angle_;
};
