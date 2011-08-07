#include "ReferenceLabel.h"

ReferenceLabel::ReferenceLabel(QWidget* parent, int chart_id, const BodyProps& props)
: AstroLabel(parent, chart_id, props)
{

}

void ReferenceLabel::setLinkedLabel(int index, AstroLabel* label)
{
	linked_ = label;
	text_ = linked_->text();
}

AstroLabel* ReferenceLabel::linkedLabel(int index)
{
	return linked_;
}
