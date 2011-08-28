#ifndef SPECULUMHORIZHEADER_H
#define SPECULUMHORIZHEADER_H

#include "SpeculumCell.h"

class SpeculumHorizHeader : public SpeculumCell
{
public:
	SpeculumHorizHeader(int column, int row, const SpeculumColors* colors);
	virtual void draw(QPainter* painter);
};

#endif // SPECULUMHORIZHEADER_H
