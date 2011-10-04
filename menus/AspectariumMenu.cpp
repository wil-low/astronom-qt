#include "AspectariumMenu.h"

#include "../utils/Aspect.h"
#include "../utils/AspectProps.h"
#include "../utils/SettingsManager.h"

#include <QAction>

AspectariumMenu::AspectariumMenu(QWidget *parent)
: QMenu(parent)
{
}

void AspectariumMenu::init(const Aspect& aspect)
{
    clear();
    const SettingsManager& sm = SettingsManager::get_const_instance();
	if (aspect.angleProps_) {
		QAction* act = addAction(QString(aspect.angleProps_->angleChar()) + " " +
								 aspect.body_[0].label_ + aspect.body_[1].label_);
		act->setFont(*sm.font(font().pointSize(), FF_ASTRO));
	}
	if (aspect.signProps_) {
		QAction* act = addAction(QString(aspect.signProps_->signChar()) + " " +
								 aspect.body_[0].label_ + aspect.body_[1].label_);
		act->setFont(*sm.font(font().pointSize(), FF_ASTRO));
	}
}
