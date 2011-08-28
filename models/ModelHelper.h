#ifndef MODELHELPER_H
#define MODELHELPER_H

#include "../utils/TimeLoc.h"

class HouseProps;
class BodyProps;
class QAbstractItemModel;

class ModelHelper
{
public:
	ModelHelper(const TimeLoc& tl, QAbstractItemModel* model, int chart_index, bool clear = false);
	void insertPlanet(int planet_id, bool isVisible);
	void insertHouses();
	bool propsByIndex(int idx, int chart_id, BodyProps* bp) const;

private:
	TimeLoc tl_;
	QAbstractItemModel* model_;
	int chart_index_;
	void addHouse (int id, const HouseProps& props, int cusp_count);
};

#endif // MODELHELPER_H
