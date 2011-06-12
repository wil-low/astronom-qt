#ifndef BASECENTRALVIEW_H
#define BASECENTRALVIEW_H

class BodyHolder
{
public:
	BodyHolder();
	virtual void insertPlanet() = 0;
	virtual void insertHouse() = 0;
};

#endif // BASECENTRALVIEW_H
