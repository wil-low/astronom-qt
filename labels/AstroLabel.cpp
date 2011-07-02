#include "AstroLabel.h"
#include <QFont>
#include <QPainter>
#include <QDebug>

#include "../utils/SettingsManager.h"

int AstroLabel::unique_id_ = 20000;
AstroLabel::LabelTypeMap AstroLabel::type_map_;

AstroLabel::AstroLabel(QWidget* parent, int chart_id, const BodyProps& props)
: rect_(0, 0, 0, 0)
, font_(NULL)
, selected_(false)
, flags_(0)
, parent_(parent)
, visible_(true)
, props_(props)
, chart_id_(chart_id)
{
	setProps(props);
	++type_map_[props_.type];
}

AstroLabel::~AstroLabel(void)
{
	--type_map_[props_.type];
}

int AstroLabel::id() const
{
	return props_.id;
}

int AstroLabel::chartId() const
{
	return chart_id_;
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

void AstroLabel::setFont(QFont* font)
{
	font_ = font;
	QFontMetrics fm(*font_);
	rect_ = fm.tightBoundingRect(text_);
/*
	rect_.setHeight(font_->pointSize() * 1.5);
	rect_.setWidth(font_->pointSize() * 1.5);
*/
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
	painter->setPen(selected_? Qt::red : Qt::black);
	//painter->drawRect(rect_);
	painter->drawText(rect_, Qt::AlignHCenter | Qt::TextDontClip, text_);
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
	return props_.type;
}

bool AstroLabel::contains(const QPoint& point) const
{
	//qDebug() << toString() << rect_ << ", " << point;
	return rect_.contains(point);
}

const QRectF& AstroLabel::rect() const
{
	return rect_;
}

QString AstroLabel::toString() const
{
	QString s;
	s.sprintf ("AstroLabel type %d, id %d, angle %.2f, visible angle %.2f",
			   type(), id(), angle(), visibleAngle());
	return s;
}

unsigned int AstroLabel::identity() const
{
	return (chartId() << 24) + (type() << 16) + (id());
}

void AstroLabel::setChartId(int chart_id)
{
	chart_id_ = chart_id;
}

void AstroLabel::setVisible(bool visible)
{
	visible_ = visible;
}

bool AstroLabel::visible() const
{
	return visible_;
}

void AstroLabel::setSelected(bool selected)
{
	selected_ = selected;
}

void AstroLabel::setProps(const BodyProps& props)
{
	props_ = props;
	text_ = SettingsManager::get_const_instance().label(props_);
}

qreal AstroLabel::prop(BodyProps::body_property p) const
{
	return props_.prop[p];
}

int AstroLabel::getUniqueId()
{
	return ++unique_id_;
}

int AstroLabel::userData() const
{
	return props_.userData;
}

QString AstroLabel::statistics()
{
	QString str("AstroLabel - ");
	QTextStream out(&str);
	LabelTypeMap::const_iterator it = type_map_.constBegin();
	while (it != type_map_.constEnd()) {
		out << it.key() << ": " << it.value() << ", ";
		++it;
	}
	return str;
}
