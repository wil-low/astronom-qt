#ifndef COORDLINEEDIT_H
#define COORDLINEEDIT_H

#include <QLineEdit>
#include "../utils/DMS.h"

class CoordLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CoordLineEdit(QWidget *parent = 0);
	void setCoordType(DMS::coord_t coord_type);

signals:

public slots:

private:
	DMS::coord_t coord_type_;
};

#endif // COORDLINEEDIT_H
