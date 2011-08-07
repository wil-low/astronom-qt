#ifndef OCULARWHEEL_H
#define OCULARWHEEL_H

#include "CentralView.h"

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
	ODIM_LAST
};

struct OcularDimensions {
};

struct OcularColors {
	QColor ocularColor;
	QColor contourColor;
	QColor mainLineColor;
	QColor labelColor;
	QColor fillColor;
	QColor arrowColor;
	QColor cuspidColor;
	QColor tick10Color;
	QColor innerRColor;
	QColor planetTickColor;
	QColor aspectTickColor;
};

class AstroLabel;

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
signals:

public slots:
	void reconfigure();
	void invalidateView();

protected:
	virtual bool isIndexHidden(const QModelIndex &index) const;

private:
	void spreadLabels (int chart, int type, qreal r);
	void drawLabels(QPainter* painter);
	void reorderLabels();
	void drawPlanetLines(QPainter* painter);
	void drawHouseLines(QPainter* painter);
	void drawAspects(QPainter* painter);

	AstroLabel* findByIndex (const QModelIndex & index) const;

	qreal defaultDimensions_[ODIM_LAST];
	qreal dimensions_[ODIM_LAST];
	OcularColors colors_;
	ZeroPoint zeroPoint_;
	qreal zeroAngle_;
};

#endif // OCULARWHEEL_H
