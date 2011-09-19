#ifndef OCULARWHEEL_H
#define OCULARWHEEL_H

#include "CentralView.h"
#include "colors/OcularColors.h"

// zero point of wheel
enum ZeroPoint {
	ZERO_ASC = 0,
	ZERO_ARIES = 1,
};

enum OcularDimensionType {
	ODIM_radius = 0,
	// all lengths in points
	ODIM_ascArrowR, // main arrow
	ODIM_zodiacOuterR, // ring of interleaved signs
	ODIM_zodiac10dgrR,
	ODIM_zodiac5dgrR,
	ODIM_zodiac30dgrR,
	ODIM_innerPlanetLabelR,
	ODIM_innerPlanetDegreeLabelR,
	ODIM_innerPlanetRetrogradeLabelR,
	ODIM_innerPlanetR,
	ODIM_zodiacInner2R,
	ODIM_zodiacInnerR,
	ODIM_aspectR,
	ODIM_planetFontSize,
	ODIM_zodiacFontSize,
	ODIM_degreeFontSize,
	ODIM_tick10Size,
	ODIM_tick5Size,
	ODIM_centerGripR,
	ODIM_LAST
};

class OcularView : public CentralView
{
	Q_OBJECT
public:
	OcularView(QWidget *parent = 0);
	void recalcDimensions(qreal newRadius);
	void recalcDimensionsByFactor(qreal factor);
	void paintEvent(QPaintEvent* event);
	virtual QModelIndex indexAt(const QPoint &point) const;
	virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
	virtual void currentChanged (const QModelIndex & current, const QModelIndex & previous);
	virtual QPoint translatePoint(const QPoint& p) const;
	virtual void restoreState(QSettings& settings);
	virtual void saveState(QSettings& settings);
	virtual void reconfigure();

	void setAspectModel(QAbstractItemModel* aspectModel);

signals:
public slots:
	void invalidateView();

protected:
	virtual bool isIndexHidden(const QModelIndex &index) const;
	virtual bool viewportEvent (QEvent* event);

private:
	void spreadLabels (int chart, int type, qreal r);
	void drawLabels(QPainter* painter);
	void reorderLabels();
	void drawPlanetLines(QPainter* painter);
	void drawHouseLines(QPainter* painter);
	void drawAspects(QPainter* painter);

	qreal defaultDimensions_[ODIM_LAST];
	qreal dimensions_[ODIM_LAST];
	OcularColors colors_;
	ZeroPoint zeroPoint_;
	qreal zeroAngle_;
	QPointF centerPoint_;
	int radius_;

	enum cursor_mode_t {
		cm_None = 0,
		cm_Pan,
		cm_Resize,
	};
	cursor_mode_t cursorMode_;
	bool mousePressed_;
	QAbstractItemModel* aspectModel_;
};

#endif // OCULARWHEEL_H
