#ifndef SPECULUMVIEW_H
#define SPECULUMVIEW_H

#include <QAbstractItemView>

class AstroLabelContainer;

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
signals:

public slots:
	void reconfigure();

private:
	void drawLabels (QPainter* painter);
	void reorderLabels();
	AstroLabelContainer* labels_;
	qreal cellWidth_;
	qreal cellHeight_;
};

#endif // SPECULUMVIEW_H
