#ifndef CENTRALVIEW_H
#define CENTRALVIEW_H

#include <QAbstractItemView>
#include "../utils/constants.h"

class AstroLabel;
class AstroLabelContainer;
class QSettings;

class CentralView : public QAbstractItemView
{
    Q_OBJECT
public:
	CentralView(QWidget *parent, doc_mode_t type);
	virtual ~CentralView();
	doc_mode_t type() const;
	virtual QRect visualRect(const QModelIndex &index) const;
	virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible);
	virtual QPoint translatePoint(const QPoint& p) const;
	virtual void restoreState(QSettings& settings) = 0;
	virtual void saveState(QSettings& settings) = 0;
	virtual void reconfigure() = 0;

	void setAspectModel(QAbstractItemModel* aspectModel);

signals:

public slots:

protected:
	virtual void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command);
	virtual QRegion visualRegionForSelection(const QItemSelection &selection) const;

	virtual QModelIndex moveCursor(CursorAction cursorAction,
								   Qt::KeyboardModifiers modifiers);
	virtual int horizontalOffset() const;
	virtual int verticalOffset() const;
	virtual bool viewportEvent (QEvent* event);

	AstroLabel* findByIndex (const QModelIndex & index) const;

	AstroLabelContainer* labels_;
	QString colorScheme_;
	QAbstractItemModel* aspectModel_;

private:
	doc_mode_t type_;
};

#endif // CENTRALVIEW_H
