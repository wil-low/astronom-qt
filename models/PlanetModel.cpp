#include "PlanetModel.h"
#include "utils/Ephemeris.h"
#include <QFont>

PlanetModel::PlanetModel(int chart_count)
	: bodies_(chart_count)
{
}

void PlanetModel::setTimeLoc(int chart_index, const TimeLoc & tl)
{
	time_loc_ = tl;
	int bodies[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 16, 17, 18};
	BodyProps props;
	for (int i =  0; i < sizeof(bodies) / sizeof(int); ++i) {
		Ephemeris::calc_body (props, bodies[i], 0, time_loc_);
		bodies_[chart_index][bodies[i]] = props;
	}
}

int PlanetModel::rowCount ( const QModelIndex & parent ) const
{
	return 10;
}

int PlanetModel::columnCount ( const QModelIndex & parent ) const
{
	return 3;
}

QVariant PlanetModel::data ( const QModelIndex & index, int role ) const
{
	if (role == Qt::DisplayRole)
		return bodies_[index.column()][index.row()].prop[BodyProps::bp_Lon];
	return QVariant();
}

QVariant PlanetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Vertical) {
		if (role == Qt::DisplayRole) {
			QString s;
			s.sprintf("%c", 'a' + section);
			return s;
		}
		if (role == Qt::FontRole)
			return QFont("Astronom", 12);
	}
	return QVariant();
}
