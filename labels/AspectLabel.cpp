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
	linked_.at(index) = label;
}

AstroLabel* AspectLabel::linkedLabel(int index)
{
	return linked_.at(index);
}

qreal AspectLabel::angle() const
{
	return linked_.at(0)->angle();
}
