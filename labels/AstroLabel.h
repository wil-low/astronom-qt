#pragma once
#include "../utils/constants.h"
#include "../utils/BodyProps.h"
#include <QtGlobal>
#include <QRectF>
#include <QString>
class QWidget;
class QFont;
class QPainter;

class AstroLabel
{
public:
	AstroLabel(QWidget* parent, int chart_id, const BodyProps& props);
	virtual ~AstroLabel(void);

	virtual qreal angle() const;
	virtual qreal visibleAngle() const;
	body_type_t type() const;
	const QRectF& rect() const;
	const QString& text() const;
	int chartId() const;
	int id() const;
	int flags() const;
	unsigned int identity() const;
	QFont* font() const;
	qreal prop(BodyProps::body_property p) const;
	QWidget* parent() const;
	int userData() const;

	void setId(int id, const QString& text);
	void setChartId(int id);
	void setFont(QFont* font);
	void setFlags(int flags);

	virtual void setProps(const BodyProps& props);

	virtual void setVisibleAngle(qreal /*ang*/) {}

	virtual QString toString() const;

	bool contains(const QPoint& point) const;
	virtual void position(qreal x, qreal y, qreal w = -1, qreal h = -1);

    void setVisible(bool visible);
	bool visible() const;

	void setSelected(bool selected);
	virtual void drawOnParent(QPainter* painter);

	virtual void setLinkedCount(int count) {}
	virtual void setLinkedLabel(int index, AstroLabel* label) {}
	virtual AstroLabel* linkedLabel(int index) {return NULL;}

	AstroLabel(){}

	static int getUniqueId();

protected:
	QRectF rect_;
	QFont* font_;
	QString text_;
    bool selected_;
	int chart_id_;
	int flags_;
	BodyProps props_;
	QWidget* parent_;
	bool visible_;

private:
	static int unique_id_;
};
