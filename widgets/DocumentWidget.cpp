#include "DocumentWidget.h"

#include <QVBoxLayout>

DocumentWidget::DocumentWidget(QWidget *parent, doc_mode_t viewType)
: QWidget(parent)
, viewType_(viewType)
, view_(NULL)
{
}
