#ifndef SPECULUMCELL_H
#define SPECULUMCELL_H

#include <QRect>
#include <list>

class AstroLabel;
class QPainter;

class SpeculumCell
{
public:
	enum category_t {
		cat_First = 0,
		cat_Second = 1,
		cat_Last,
	};
	SpeculumCell(int column, int row);
	void clear();
	void addLabel(category_t category, AstroLabel* label);
	void reconfigure(qreal cellWidth, qreal cellHeight, int fontSize);
	void draw(QPainter* painter);
private:
	std::list<AstroLabel*> labels_[cat_Last];
	QRect rect_;
	int column_;
	int row_;
	int fontSize_;
	qreal cellWidth_;
	qreal cellHeight_;
};

#endif // SPECULUMCELL_H
