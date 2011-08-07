#include "AspectLabel.h"
#include <stdexcept>
#include "../utils/SettingsManager.h"
#include "../utils/CRC32.h"

AspectLabel::AspectLabel(QWidget* parent, int chart_id, const BodyProps& props)
: AstroLabel(parent, chart_id, props)
{
}

void AspectLabel::setLinkedCount(int count)
{
	linked_.resize(count);
}

void AspectLabel::setLinkedLabel(int index, AstroLabel* label)
{
	try {
		linked_.at(index) = label;
	}
	catch (std::out_of_range&) {}
}

AstroLabel* AspectLabel::linkedLabel(int index)
{
	try {
		return linked_.at(index);
	}
	catch (std::out_of_range&) {}
	return NULL;
}
