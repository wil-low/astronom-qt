#ifndef OCULARSCENE_H
#define OCULARSCENE_H

#include "ModelledScene.h"

// zero point of wheel
enum ZeroPoint {
	ZERO_ASC = 0,
	ZERO_ARIES = 1,
};

struct OcularDimensions {
	int radius;
	// all lengths in points
	int ascArrowR; // main arrow
	int zodiacOuterR; // ring of interleaved signs
	int zodiac10dgrR;
	int zodiac5dgrR;
	int zodiac30dgrR;
	int innerPlanetLabelR;
	int innerPlanetR;
	int zodiacInner2R;
	int zodiacInnerR;
	int aspectR;
	int planetFontSize;
	int zodiacFontSize;
	int degreeFontSize;
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

class OcularScene : public ModelledScene
{
    Q_OBJECT
public:
    explicit OcularScene(QObject *parent = 0);
	void reorderItems();
signals:

public slots:
	void reconfigure();
protected:
	void drawBackground (QPainter* painter, const QRectF& rect);

private:
	void drawCircle(QPainter* painter, qreal radius);
	void drawArc(QPainter* painter, qreal radius, qreal startAngle, qreal spanAngle);
	void drawPie(QPainter* painter, qreal radius, qreal startAngle, qreal spanAngle);
	QPointF getXYdeg(qreal degree, qreal len);
	void addZodiacSigns();

	OcularDimensions dimensions_;
	OcularColors colors_;
	int zeroAngle_;
	ZeroPoint zeroPoint_;
};

#endif // OCULARSCENE_H
