#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include "../utils/constants.h"
#include <QWidget>

class QSplitter;
class CentralView;
class QAbstractItemModel;
class QSettings;

class DocumentWidget : public QWidget
{
    Q_OBJECT
public:
	DocumentWidget(const QObject* manager, doc_mode_t viewType, QAbstractItemModel* model);
	void saveState(QSettings& settings);
	void restoreState(QSettings& settings);

signals:

public slots:
	void reconfigure();
        void updateViews();
private:
	doc_mode_t viewType_;
	QSplitter* vertSplitter_;
	QSplitter* horizSplitter_;
	CentralView* view_;
};

#endif // DOCUMENTWIDGET_H
