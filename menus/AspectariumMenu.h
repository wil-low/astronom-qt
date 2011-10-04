#ifndef ASPECTARIUMMENU_H
#define ASPECTARIUMMENU_H

#include <QMenu>

class Aspect;

class AspectariumMenu : public QMenu
{
    Q_OBJECT
public:
    explicit AspectariumMenu(QWidget *parent = 0);
    void init(const Aspect& aspect);
signals:

public slots:

};

#endif // ASPECTARIUMMENU_H
