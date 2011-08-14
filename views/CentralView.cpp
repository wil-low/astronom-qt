#include "CentralView.h"
#include "../labels/AstroLabelContainer.h"
#include "../utils/css.h"
#include <QEvent>
#include <QHelpEvent>
#include <QToolTip>

CentralView::CentralView(QWidget *parent, central_view_t type)
: QAbstractItemView(parent)
, labels_(new AstroLabelContainer)
, type_(type)
{
	setProperty(CSS::MarineBackground, true);
}

CentralView::~CentralView()
{
	delete labels_;
}

QRect CentralView::visualRect(const QModelIndex &index) const
{
	return QRect(0,0,0,0);
}

void CentralView::scrollTo(const QModelIndex &index, ScrollHint hint)
{

}

QModelIndex CentralView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
	return QModelIndex();
}

int CentralView::horizontalOffset() const
{
	return 0;
}

int CentralView::verticalOffset() const
{
	return 0;
}

void CentralView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
	//qDebug() << rect;
}

QRegion CentralView::visualRegionForSelection(const QItemSelection &selection) const
{
	return QRegion();
}

bool CentralView::viewportEvent (QEvent* event)
{
	if (event->type() == QEvent::ToolTip) {
		QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
		AstroLabel* label = labels_->labelAt(translatePoint(helpEvent->pos()));
		if (label) {
			QToolTip::showText(helpEvent->globalPos(), label->toString());
		} else {
			QToolTip::hideText();
			event->ignore();
		}
		return true;
	}
	return QAbstractItemView::viewportEvent(event);
}

QPoint CentralView::translatePoint(const QPoint& p) const
{
	return p;
}

AstroLabel* CentralView::findByIndex (const QModelIndex & index) const
{
	int chart_id = index.column();
	BodyProps props = model()->data(index).value<BodyProps>();
	return labels_->find_by_chart_id(chart_id, props.id);
}
