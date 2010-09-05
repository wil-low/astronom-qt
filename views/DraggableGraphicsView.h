#ifndef DRAGGABLEGRAPHICSVIEW_H
#define DRAGGABLEGRAPHICSVIEW_H

#include <QGraphicsView>

class DraggableGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
	DraggableGraphicsView(QWidget *parent);

signals:

public slots:

protected:/*
	void mousePressEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);*/
private:
	bool isMousePressed_;
};

#endif // DRAGGABLEGRAPHICSVIEW_H
