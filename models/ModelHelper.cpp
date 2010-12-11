#include "ModelHelper.h"
#include "../utils/BodyProps.h"
#include "../utils/HouseProps.h"
#include "../utils/Ephemeris.h"
#include <QAbstractItemModel>

ModelHelper::ModelHelper(const TimeLoc& tl, QAbstractItemModel* model, int chart_index, bool clear)
: tl_(tl), model_(model), chart_index_(chart_index)
{
	if (clear)
		model_->removeRows(chart_index, model_->rowCount(QModelIndex()), QModelIndex());
}

void ModelHelper::insertPlanet(int planet_id)
{
	BodyProps props;
	int row = model_->rowCount();
	model_->insertRows(row, 1, QModelIndex());
	Ephemeris::calc_body (props, planet_id, 0, tl_);
	props.id = planet_id;
	props.type = TYPE_PLANET;
	model_->setData (model_->index(row, chart_index_, QModelIndex()), qVariantFromValue(props));
}

void ModelHelper::insertHouses()
{
	HouseProps houses;
	Ephemeris::calc_house(houses, tl_);
	int cusp_count = tl_.cuspCount();
//	addHouse(chart_index, HOUSE_ID_ASC, houses);
//	addHouse(chart_index, HOUSE_ID_MC, houses);
	for (int i = 0; i < tl_.cuspCount(); ++i)
		addHouse(HOUSE_ID_FIRST + i, houses, cusp_count);
}

void ModelHelper::addHouse (int id, const HouseProps& props, int cusp_count)
{
	int row = model_->rowCount();
	model_->insertRows(row, 1, QModelIndex());
	BodyProps hprops;
	hprops.id = id;
	hprops.type = TYPE_HOUSE;
	hprops.userData = cusp_count;
	hprops.prop[BodyProps::bp_Lon] = (id >= HOUSE_ID_FIRST) ?
									 props.cusps[id - HOUSE_ID_FIRST + 1] :
									 props.ascmc[id - HOUSE_ID_ASC];
	model_->setData (model_->index(row, chart_index_, QModelIndex()), qVariantFromValue(hprops));
}

