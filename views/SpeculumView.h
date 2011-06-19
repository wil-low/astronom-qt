#ifndef SPECULUMVIEW_H
#define SPECULUMVIEW_H

#include <QAbstractItemView>
#include "../utils/constants.h"

class AstroLabel;
class AstroLabelContainer;
class SpeculumCell;
class BodyProps;

class SpeculumView : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit SpeculumView(QWidget *parent = 0);
	virtual ~SpeculumView();
	virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

	void paintEvent(QPaintEvent* event);
	virtual QRect visualRect(const QModelIndex &index) const;
	virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible);
	virtual QModelIndex indexAt(const QPoint &point) const;
	virtual void currentChanged (const QModelIndex & current, const QModelIndex & previous);

protected:
	virtual QModelIndex moveCursor(CursorAction cursorAction,
								   Qt::KeyboardModifiers modifiers);
	virtual int horizontalOffset() const;
	virtual int verticalOffset() const;

	virtual bool isIndexHidden(const QModelIndex &index) const;

	virtual void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command);
	virtual QRegion visualRegionForSelection(const QItemSelection &selection) const;
	virtual void resizeEvent (QResizeEvent* event);
	virtual bool viewportEvent (QEvent* event);

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
	AstroLabelContainer* labels_;
	qreal cellWidth_;
	qreal cellHeight_;
	SpeculumCell* cells_[COLUMN_COUNT * ROW_COUNT];
	void clearCells();
};

#endif // SPECULUMVIEW_H
