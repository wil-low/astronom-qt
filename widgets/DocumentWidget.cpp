#include "DocumentWidget.h"

#include <QVBoxLayout>

DocumentWidget::DocumentWidget(QWidget *parent, central_view_t viewType)
: QWidget(parent)
, viewType_(viewType)
, view_(NULL)
{
}
