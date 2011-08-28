#include "SpeculumView.h"
#include "../utils/BodyProps.h"
#include "../labels/AstroLabelContainer.h"
#include "../labels/LabelFactory.h"
#include "../utils/SettingsManager.h"
#include "../utils/DMS.h"
#include "items/SpeculumCell.h"
#include "items/SpeculumVertHeader.h"
#include "items/SpeculumHorizHeader.h"
#include "../utils/CRC32.h"

#include <boost/foreach.hpp>

#include <QSettings>
#include <QPainter>
#include <QDebug>

SpeculumView::SpeculumView(QWidget *parent)
: CentralView(parent, doc_Speculum)
, cellWidth_(0)
, cellHeight_(0)
{
	setSelectionMode(QAbstractItemView::SingleSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	SpeculumCell* cell = NULL;
	for (int column = 0; column < COLUMN_COUNT; ++column)
		for (int row = 0; row < ROW_COUNT; ++row) {
			if (column == 0 && row > 0)
				cell = new SpeculumVertHeader(column, row, &colors_);
			else if (column > 0 && row == 0 && column != COLUMN_COUNT - 1)
				cell = new SpeculumHorizHeader(column, row, &colors_);
			else
				cell = new SpeculumCell(column, row, &colors_);

			cells_[row * COLUMN_COUNT + column] = cell;
		}
}

SpeculumView::~SpeculumView()
{
	BOOST_FOREACH(SpeculumCell* cell, cells_)
		delete cell;
}

void SpeculumView::reconfigure()
{
//	restoreState();

	BOOST_FOREACH(SpeculumCell* cell, cells_) {
		cell->sort();
		cell->reconfigure(cellWidth_, cellHeight_, speculum::DEFAULT_FONT_SIZE);
	}
//	viewport()->update();
}

void SpeculumView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
	QAbstractItemView::dataChanged(topLeft, bottomRight);
//	qDebug() << __FUNCTION__ << topLeft.column() << "/" << topLeft.row()
//			<< ", " << bottomRight.column() << "/" << bottomRight.row();
	clearCells();
	int chart_id = 0;
	for (int row = 0; row < model()->rowCount(rootIndex()); ++row) {
		QModelIndex index = model()->index(row, chart_id, rootIndex());
		BodyProps props = model()->data(index).value<BodyProps>();
		bool isVisible = index.data(Qt::VisibilityRole).toBool();
		DMS dms(props.prop[BodyProps::bp_Lon], DMS::COORD_LON);
		int column = dms.zodiac() + 1;
		int row = dms.zod_deg() + 1;
		if (props.type == TYPE_HOUSE) {
			props.flags |= FLG_ARABIC;
			AstroLabel* label = insertLabel(chart_id, props, isVisible,
											column, row, speculum::cat_First,
											colors_.houseColor);
			//addReference(label);
		}
		else if (props.type == TYPE_PLANET) {
			AstroLabel* label = insertLabel(chart_id, props, isVisible,
											column, row, speculum::cat_First,
											colors_.planetColor);
			addAspects(label);
			addReference(label);
		}
	}
	reconfigure();
}

void SpeculumView::paintEvent(QPaintEvent* event)
{
	QPainter painter(viewport());

	painter.save();
	painter.translate(0, cellHeight_);
	QLineF horizLine (0, 0, viewport()->width(), 0);
	QColor* penColor;
	for (int i = 0; i < ROW_COUNT; ++i) {
		switch (i) {
		case 0:
		case ROW_COUNT - 1:
			penColor = &colors_.contourColor;
			break;
		case DEG_PER_SIGN / 2:
			penColor = &colors_.middleColor;
			break;
		default:
			penColor = &colors_.gridColor;
			break;
		}
		painter.setPen(*penColor);
		painter.drawLine(horizLine);
		horizLine.translate(0, cellHeight_);
	}
	painter.restore();
	painter.save();
	painter.translate(cellWidth_, 0);
	QLineF vertLine (0, 0, 0, viewport()->height());
	for (int i = 0; i < COLUMN_COUNT; ++i) {
		switch (i) {
		case 0:
		case COLUMN_COUNT - 2:
			penColor = &colors_.contourColor;
			break;
		case ZODIAC_SIGN_COUNT / 2:
			penColor = &colors_.middleColor;
			break;
		default:
			penColor = &colors_.gridColor;
			break;
		}
		painter.setPen(*penColor);
		painter.drawLine(vertLine);
		vertLine.translate(cellWidth_, 0);
	}
	painter.restore();
	drawCells(&painter);
}

QModelIndex SpeculumView::indexAt(const QPoint &point) const
{
	AstroLabel* cur_al = labels_->labelAt(translatePoint(point));
	if (cur_al) {
		int chart_id = cur_al->chartId();
		int id = cur_al->id();
		int rowCount = model()->rowCount();
		for (int i = 0; i < rowCount; ++i) {
			QModelIndex index = model()->index(i, chart_id);
			const BodyProps& props = model()->data(index).value<BodyProps>();
			if (props.id == id)
				return index;
		}
	}
	return QModelIndex();
}

bool SpeculumView::isIndexHidden(const QModelIndex &index) const
{
	return false;
}

void SpeculumView::drawCells (QPainter* painter)
{
	BOOST_FOREACH (SpeculumCell* cell, cells_) {
		cell->draw(painter);
//		qDebug() << "draw " << al->toString() << ", text '" << al->text() << ", " << al->rect();
	}
}

void SpeculumView::resizeEvent (QResizeEvent* event)
{
	cellWidth_ = (qreal)viewport()->width() / COLUMN_COUNT;
	cellHeight_ = (qreal)viewport()->height() / ROW_COUNT;
	reconfigure();
}

void SpeculumView::clearCells()
{
	BOOST_FOREACH(SpeculumCell* cell, cells_)
		cell->clear();
}

AstroLabel* SpeculumView::insertLabel(int chart_id, const BodyProps& props, bool isVisible,
									  int column, int row, speculum::category_t category,
									  const QColor& color)
{
	AstroLabel* label = labels_->find_by_chart_id(chart_id, props.id);
	bool need_insert = !label;
	if (!label)
		label = LabelFactory::construct(this, chart_id, props);
	label->setProps(props);
	label->setChartId(chart_id);
	label->setVisible(isVisible);
	label->setColor(color, false); // set inactive color
	if (need_insert) {
		std::pair<AlcIter, bool> result = labels_->insert(label);
		assert (result.second);
	}
	cells_[row * COLUMN_COUNT + column]->addLabel(category, label);
	return label;
}

void SpeculumView::addAspects (AstroLabel* parentLabel)
{
	static const double ASPECT_ANGLES[] = {
		180, 120, 90, 60,
	};
	int column, row;
	BOOST_FOREACH(const double& angle, ASPECT_ANGLES) {
		BodyProps props;
		props.type = TYPE_ASPECT;
		props.userData = (int)angle;
		props.prop[BodyProps::bp_AspectAngle] = angle;
		// positive angle
		int checksumArray[] = {parentLabel->id(), parentLabel->id(), (int)angle};
		props.id = Crc32((const unsigned char*)checksumArray, sizeof(checksumArray));
		props.prop[BodyProps::bp_Lon] = BodyProps::normalize(
				parentLabel->prop(BodyProps::bp_Lon) + angle, ZODIAC_SIGN_COUNT * DEG_PER_SIGN);
		DMS dms(props.prop[BodyProps::bp_Lon], DMS::COORD_LON);
		column = dms.zodiac() + 1;
		row = dms.zod_deg() + 1;
		AstroLabel* aspect = insertLabel(parentLabel->chartId(), props, parentLabel->visible(),
										column, row, speculum::cat_First, colors_.aspectColor);
		aspect->setColor(colors_.aspectSelectedColor, true);
		aspect->setLinkedCount(1);
		aspect->setLinkedLabel(0, parentLabel);
		// negative angle
		if ((int)angle != 180) {
			int checksumArray[] = {parentLabel->id(), parentLabel->id(), (int)-angle};
			props.id = Crc32((const unsigned char*)checksumArray, sizeof(checksumArray));
			props.prop[BodyProps::bp_Lon] = BodyProps::normalize(
					parentLabel->prop(BodyProps::bp_Lon) - angle, ZODIAC_SIGN_COUNT * DEG_PER_SIGN);
			DMS dms(props.prop[BodyProps::bp_Lon], DMS::COORD_LON);
			column = dms.zodiac() + 1;
			row = dms.zod_deg() + 1;
			aspect = insertLabel(parentLabel->chartId(), props, parentLabel->visible(),
								 column, row, speculum::cat_First, colors_.aspectColor);
			aspect->setColor(colors_.aspectSelectedColor, true);
			aspect->setLinkedCount(1);
			aspect->setLinkedLabel(0, parentLabel);
		}
	}
}

void SpeculumView::addReference (AstroLabel* parentLabel)
{
	BodyProps props(parentLabel->props());
	props.type = TYPE_REFERENCE;
	int checksumArray[] = {(int)parentLabel};
	props.id = Crc32((const unsigned char*)checksumArray, sizeof(checksumArray));
	DMS dms(props.prop[BodyProps::bp_Lon], DMS::COORD_LON);
	int column = 0;
	int row = dms.zod_deg() + 1;
	AstroLabel* label = insertLabel(parentLabel->chartId(), props, parentLabel->visible(),
									column, row, speculum::cat_Second, colors_.referenceColor);
	label->setLinkedLabel(0, parentLabel);
}

void SpeculumView::currentChanged (const QModelIndex & current, const QModelIndex & previous)
{
	AstroLabel* label = findByIndex(previous);
	if (label) {
		label->setSelected(false);
		selectAspects(label, false);
	}
	label = findByIndex(current);
	if (label) {
		label->setSelected(true);
		selectAspects(label, true);
	}
	viewport()->update();
}

void SpeculumView::selectAspects (const AstroLabel* parentLabel, bool isSelected)
{
	BOOST_FOREACH (AstroLabel* al, *labels_) {
		if (al->type() == TYPE_ASPECT && al->linkedLabel(0) == parentLabel)
			al->setSelected(isSelected);
	}
}

void SpeculumView::restoreState(QSettings& settings)
{
	settings.beginGroup("colors");
	colorScheme_ = settings.value("colorScheme", "default").toString();
	settings.beginGroup(colorScheme_);
	colors_.headerColor = settings.value("headerColor", QColor(255,204,102)).value<QColor>(); // orange
	colors_.planetColor = settings.value("planetColor", QColor(0,0,0)).value<QColor>(); // black
	colors_.houseColor = settings.value("houseColor", QColor(0,0,0)).value<QColor>(); // black
	colors_.aspectColor = settings.value("aspectColor", QColor(67,0,134)).value<QColor>(); // dye violet
	colors_.aspectSelectedColor = settings.value("aspectSelectedColor", QColor(184,54,54)).value<QColor>(); // dye violet
	colors_.referenceColor = settings.value("referenceColor", QColor(67,0,134)).value<QColor>(); // dye violet
	colors_.gridColor = settings.value("gridColor", QColor(78,84,136)).value<QColor>(); // dye violet
	colors_.contourColor = settings.value("contourColor", QColor(0,0,0)).value<QColor>(); // black
	colors_.middleColor = settings.value("middleColor", QColor(176,176,176)).value<QColor>(); // gray
	settings.endGroup();
	settings.endGroup();
}

void SpeculumView::saveState(QSettings& settings)
{
	settings.beginGroup("colors");
	settings.setValue("colorScheme", colorScheme_);
	settings.beginGroup(colorScheme_);
	settings.setValue("headerColor", colors_.headerColor); // orange
	settings.setValue("planetColor", colors_.planetColor); // black
	settings.setValue("houseColor", colors_.houseColor); // black
	settings.setValue("aspectColor", colors_.aspectColor); // dye violet
	settings.setValue("aspectSelectedColor", colors_.aspectSelectedColor); // dye violet
	settings.setValue("referenceColor", colors_.referenceColor); // dye violet
	settings.setValue("gridColor", colors_.gridColor); // dye violet
	settings.setValue("contourColor", colors_.contourColor); // black
	settings.setValue("middleColor", colors_.middleColor); // gray
	settings.endGroup();
	settings.endGroup();

	settings.sync();
}
