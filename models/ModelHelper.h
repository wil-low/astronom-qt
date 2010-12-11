#ifndef MODELHELPER_H
#define MODELHELPER_H

#include "../utils/TimeLoc.h"

class HouseProps;
class QAbstractItemModel;

class ModelHelper
{
public:
	ModelHelper(const TimeLoc& tl, QAbstractItemModel* model, int chart_index, bool clear = false);
	void insertPlanet(int planet_id);
	void insertHouses();

private:
	TimeLoc tl_;
	QAbstractItemModel* model_;
	int chart_index_;
	void addHouse (int id, const HouseProps& props, int cusp_count);
};

#endif // MODELHELPER_H
