#include "ModelHelper.h"
#include "../utils/BodyProps.h"
#include "../utils/HouseProps.h"
#include "../utils/Ephemeris.h"
#include <QAbstractItemModel>

ModelHelper::ModelHelper(const TimeLoc& tl, QAbstractItemModel* model, int chart_index, bool clear)
: tl_(tl)
, model_(model)
, chart_index_(chart_index)
{
	if (clear)
		model_->removeRows(chart_index, model_->rowCount(QModelIndex()), QModelIndex());
}

void ModelHelper::insertPlanet(int planet_id, bool isVisible)
{
	BodyProps props;
	int row = model_->rowCount();
	model_->insertRows(row, 1, QModelIndex());
	Ephemeris::calc_body (props, planet_id, 0, tl_);
	props.id = planet_id;
	props.type = TYPE_PLANET;
	QModelIndex index = model_->index(row, chart_index_, QModelIndex());
	model_->setData (index, qVariantFromValue(props));
	model_->setData (index, isVisible, Qt::VisibilityRole);
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
	QModelIndex index = model_->index(row, chart_index_, QModelIndex());
	model_->setData (index, qVariantFromValue(hprops));
	model_->setData (index, true, Qt::VisibilityRole);
}

bool ModelHelper::propsByIndex(int idx, int chart_id, BodyProps* bp) const
{
	if (idx >= model_->rowCount())
		return false;
	QModelIndex index = model_->index(idx, chart_id);
	*bp = model_->data(index).value<BodyProps>();
	return true;
}
