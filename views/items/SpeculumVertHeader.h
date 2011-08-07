#ifndef SPECULUMVERTHEADER_H
#define SPECULUMVERTHEADER_H

#include "SpeculumCell.h"

class SpeculumVertHeader : public SpeculumCell
{
public:
	SpeculumVertHeader(int column, int row);
	virtual void draw(QPainter* painter);
};

#endif // SPECULUMVERTHEADER_H
