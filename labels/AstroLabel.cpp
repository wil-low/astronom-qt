#include "AstroLabel.h"
#include <QFont>
#include <QPainter>

AstroLabel::AstroLabel(QWidget* p)
: rect_(0, 0, 0, 0)
, font_(NULL)
, selected_(false)
, chart_id_(-1)
, id_(-1)
, flags_(0)
, parent_(p)
, visible_(true)
{
}

AstroLabel::~AstroLabel(void)
{
}

void AstroLabel::setChartId(int id)
{
	chart_id_ = id;
}

int AstroLabel::chartId() const
{
	return chart_id_;
}

int AstroLabel::id() const
{
	return id_;
}

int AstroLabel::flags() const
{
	return flags_;
}

QWidget* AstroLabel::parent() const
{
	return parent_;
}

void AstroLabel::setFlags(int flags)
{
	flags_ = flags;
}

void AstroLabel::setId(int id, const QString& text)
{
	id_ = id;
	text_ = text;
}

void AstroLabel::setFont(QFont* font)
{
	font_ = font;
	rect_.setHeight(30);
	rect_.setWidth(30);
}

QFont* AstroLabel::font() const
{
	return font_;
}

const QString& AstroLabel::text() const
{
	return text_;
}

void AstroLabel::drawOnParent(QPainter* painter)
{
	if (!visible_)
		return;
	painter->save();
	painter->setFont(*font_);
//    painter->setClipRectangle (rect_.x, rect_.y, rect_.w, rect_.h);
//    painter->setForeground(FXRGB(0, 0, 0));
	painter->drawText(rect_, Qt::AlignCenter, text_);
//    if (selected_)
//        onDrawFocus(o, sel, ptr);
	painter->restore();
}

/*
long AstroLabel::onClicked(FXObject*, FXSelector, void*)
{
	return 1;
}

long AstroLabel::onDrawOnParent(FXObject* o, FXSelector sel, void* ptr)
{
    if (!visible_)
        return 1;
    FXDC* dc = (FXDC*)ptr;
    dc->setFont(font_);
    dc->setClipRectangle (rect_.x, rect_.y, rect_.w, rect_.h);
    dc->setForeground(FXRGB(0, 0, 0));
    FXint tw = font_->getTextWidth(text_);
    FXint th = font_->getTextHeight(text_);
    dc->drawText(rect_.x + (rect_.w - tw) / 2, rect_.y + (rect_.h + th) / 2, text_);
    if (selected_)
        onDrawFocus(o, sel, ptr);
    return 1;
}

long AstroLabel::onDrawFocus(FXObject*, FXSelector, void* ptr)
{
    if (!visible_)
        return 1;
    FXDC* dc = (FXDC*)ptr;
    dc->setClipRectangle (rect_.x, rect_.y, rect_.w, rect_.h);
    dc->setForeground(selected_ ? FXRGB(255, 0, 0) : dc->getBackground());
    dc->drawRectangle(rect_.x, rect_.y, rect_.w - 1, rect_.h - 1);
    return 1;
}

long AstroLabel::onCmdSelect(FXObject* o, FXSelector sel, void* ptr)
{
    selected_ = ptr != 0;
//    FXTRACE((10, selected_ ? "sel\n" : "unsel\n"));
    return 1;
}
*/
void AstroLabel::position(qreal x, qreal y, qreal w, qreal h)
{
	if (w == -1)
		w = rect_.width();
	if (h == -1)
		h = rect_.height();
	rect_ = QRectF(x - w / 2, y - h / 2, w, h);
}

qreal AstroLabel::angle() const
{
    return -1;
}

qreal AstroLabel::visibleAngle() const
{
    return -1;
}

body_type_t AstroLabel::type() const
{
    return TYPE_LAST;
}

bool AstroLabel::contains(qreal x, qreal y)
{
    return rect_.contains(x, y);
}

const QRectF& AstroLabel::rect() const
{
	return rect_;
}

QString AstroLabel::toString() const
{
	QString s;
	s.sprintf ("AstroLabel type %d, id %d, angle %.2f", type(), id(), angle());
	return s;
}

unsigned int AstroLabel::identity() const
{
	return (chartId() << 24) + (type() << 16) + (id());
}

void AstroLabel::setVisible(bool visible)
{
	visible_ = visible;
}

bool AstroLabel::visible() const
{
	return visible_;
}

void AstroLabel::setProps(const BodyProps& props)
{
	props_ = props;
}

double AstroLabel::prop(BodyProps::body_property p) const
{
	return props_.prop[p];
}
