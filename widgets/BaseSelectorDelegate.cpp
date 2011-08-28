#include "BaseSelectorDelegate.h"
#include "../utils/constants.h"

BaseSelectorDelegate::BaseSelectorDelegate(QObject *parent)
: QStyledItemDelegate(parent)
, degree_mode_(dm_Unknown)
, fontSize_(5)
{
}

void BaseSelectorDelegate::restyle(int degree_mode, int fontSize)
{
	degree_mode_ = degree_mode;
	fontSize_ = fontSize;
}

QSize BaseSelectorDelegate::sizeHint(const QStyleOptionViewItem &option,
							 const QModelIndex &index) const
{
	return QStyledItemDelegate::sizeHint(option, index);
}
