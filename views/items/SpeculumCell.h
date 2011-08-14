#ifndef SPECULUMCELL_H
#define SPECULUMCELL_H

#include "SpeculumConst.h"
#include <QRect>
#include <list>

class AstroLabel;
class QPainter;
struct SpeculumColors;

class SpeculumCell
{
public:
	SpeculumCell(int column, int row, const SpeculumColors* colors);
	void clear();
	void sort();
	void addLabel(speculum::category_t category, AstroLabel* label);
	void reconfigure(qreal cellWidth, qreal cellHeight, int fontSize);
	virtual void draw(QPainter* painter);
protected:
	std::list<AstroLabel*> labels_[speculum::cat_Last];
	QRect rect_;
	int column_;
	int row_;
	int fontSize_;
	qreal cellWidth_;
	qreal cellHeight_;
	const SpeculumColors* colors_;
};

#endif // SPECULUMCELL_H
