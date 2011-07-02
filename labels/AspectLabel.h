#ifndef ASPECTLABEL_H
#define ASPECTLABEL_H

#include "AstroLabel.h"
#include <vector>

class AspectLabel : public AstroLabel
{
public:
	AspectLabel(QWidget* parent, int chart_id, const BodyProps& props);
	virtual void setLinkedCount(int count);
	virtual void setLinkedLabel(int index, AstroLabel* label);
	virtual AstroLabel* linkedLabel(int index);
	static int calculateId(int parentId0, int parentId1, int angle);
private:
	std::vector<AstroLabel*> linked_;
};

#endif // ASPECTLABEL_H
