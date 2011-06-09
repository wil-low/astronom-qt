#include "TimeOffsetEdit.h"
#include "../utils/validators/TimeOffsetValidator.h"

TimeOffsetEdit::TimeOffsetEdit(QWidget *parent)
: QLineEdit(parent)
{
	setInputMask("X00:00:00;_");
	setValidator(new TimeOffsetValidator(this));
}

QString TimeOffsetEdit::dbText() const
{
	QString txt = displayText();
	txt = txt.mid(0, 3) + txt.mid(4, 2) + txt.mid(7, 2);
	return txt;
}

void TimeOffsetEdit::setDbText(const QString& text)
{
	setText(text);
}
