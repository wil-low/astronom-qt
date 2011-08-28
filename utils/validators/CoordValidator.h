#ifndef COORDVALIDATOR_H
#define COORDVALIDATOR_H

#include <QValidator>
#include "../DMS.h"

class CoordValidator : public QValidator
{
    Q_OBJECT
public:
	explicit CoordValidator(QObject *parent, DMS::coord_t coord_type);
	virtual State validate (QString& input, int& pos) const;
signals:

public slots:

private:
	DMS::coord_t coord_type_;
};

#endif // COORDVALIDATOR_H
