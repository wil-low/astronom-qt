#ifndef PLANETMODEL_H
#define PLANETMODEL_H

#include "../utils/TimeLoc.h"
#include "../utils/BodyProps.h"
#include <QAbstractTableModel>
#include <QVector>
#include <QSet>

class PlanetModel : public QAbstractTableModel
{
public:
	PlanetModel(int chart_count);
	void setTimeLoc(int chart_index, const TimeLoc& tl);
	virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
private:
	TimeLoc time_loc_;
	QVector <QMap <int, BodyProps> > bodies_;
};

#endif // PLANETMODEL_H
