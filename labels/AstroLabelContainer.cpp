#include "AstroLabelContainer.h"

#include <boost/foreach.hpp>
#include <QPoint>

AstroLabelContainer::~AstroLabelContainer()
{
	BOOST_FOREACH (AstroLabel* al, *this)
		delete al;
	clear();
}

AstroLabel* AstroLabelContainer::find_by_chart_id (int chart, int id)
{
	alc_by_chart_id& ref = get<chart_id_tag>();
	alc_by_chart_id::iterator it = ref.find (boost::make_tuple(chart, id));
	return (it != ref.end()) ? *it : NULL;
}

AstroLabel* AstroLabelContainer::labelAt(const QPoint& point) const
{
	AstroLabel* cur_al = NULL;
	BOOST_FOREACH (AstroLabel* al, *this) {
		if (al->visible() && al->contains(point)) {
			cur_al = al;
			break;
		}
	}
	return cur_al;
}
