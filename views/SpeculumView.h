#ifndef SPECULUMVIEW_H
#define SPECULUMVIEW_H

#include "CentralView.h"
#include "../utils/constants.h"

class AstroLabel;
class SpeculumCell;
class BodyProps;

class SpeculumView : public CentralView
{
    Q_OBJECT
public:
    explicit SpeculumView(QWidget *parent = 0);
	virtual ~SpeculumView();
	virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

	void paintEvent(QPaintEvent* event);
	virtual QModelIndex indexAt(const QPoint &point) const;

protected:
	virtual bool isIndexHidden(const QModelIndex &index) const;
	virtual void resizeEvent (QResizeEvent* event);

signals:

public slots:
	void reconfigure();

private:
	static const int COLUMN_COUNT = ZODIAC_SIGN_COUNT;
	static const int ROW_COUNT = DEG_PER_SIGN;
	AstroLabel* insertLabel (int chart_id, const BodyProps& props, bool isVisible);
	void addAspects (AstroLabel* parentLabel);
	void drawHeaders (QPainter* painter);
	void drawCells (QPainter* painter);
	qreal cellWidth_;
	qreal cellHeight_;
	SpeculumCell* cells_[COLUMN_COUNT * ROW_COUNT];
	void clearCells();
};

#endif // SPECULUMVIEW_H
