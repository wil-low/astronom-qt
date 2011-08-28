#ifndef REFERENCELABEL_H
#define REFERENCELABEL_H

#include "AstroLabel.h"

class ReferenceLabel : public AstroLabel
{
public:
	ReferenceLabel(QWidget* parent, int chart_id, const BodyProps& props);
	virtual void setLinkedLabel(int index, AstroLabel* label);
	virtual AstroLabel* linkedLabel(int index);
	virtual qreal angle() const;
private:
	AstroLabel* linked_;
};

#endif // REFERENCELABEL_H
