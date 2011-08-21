#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include "../utils/constants.h"
#include <QWidget>

class QVBoxLayout;
class CentralView;

class DocumentWidget : public QWidget
{
    Q_OBJECT
public:
	DocumentWidget(QWidget *parent, central_view_t viewType);

signals:

public slots:
private:
	central_view_t viewType_;
	QVBoxLayout* layout_;
	CentralView* view_;
};

#endif // DOCUMENTWIDGET_H
