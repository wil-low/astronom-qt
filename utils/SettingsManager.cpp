#include "SettingsManager.h"
#include "AspectManager.h"
#include "../db/DBHelper.h"
#include "../utils/BodyProps.h"
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QSettings>
#include <QFont>
#include <QFile>
#include <QDir>
#include <QTextStream>

const char DELIMITER = ' ';

const QString DEG_STR("°");
const QString BACKTICK_STR("`");

const QString ASPECT_PREFIX("asp");

SettingsManager::SettingsManager()
{
}

const QString& SettingsManager::settingsPath() const
{
	return settingsPath_;
}

QSettings& SettingsManager::settings()
{
	return *settings_;
}

void SettingsManager::init()
{
	settings_ = new QSettings;
	settingsPath_ = QFileInfo(settings_->fileName()).absolutePath() + "/";
	DBHelper::get_mutable_instance().initConnections(settingsPath_);

	QFile cssFile(settingsPath_ + "/style.css");
	if (cssFile.open(QFile::ReadOnly)) {
		QTextStream in(&cssFile);
		qApp->setStyleSheet(in.readAll());
	}
	cssFile.close();

	loadFont(astrofont_, "Astronom");
	loadFont(arialfont_, "Arial");

	settings_->beginGroup("ephemeris-mapping");
	QStringList list = settings_->childKeys();
	for (int i = 0; i < list.size(); ++i) {
		QString name = list.at(i);
		int id = settings_->value(name).toInt();
		planet2id_[name] = id;
		id2planet_[id] = name;
	}
	settings_->endGroup();

	settings_->beginGroup("house-method");
	list = settings_->childKeys();
	for (int i = 0; i < list.size(); ++i) {
		QString name = list.at(i);
		house_method_.push_back(StringPair(name, settings_->value(name).toString()));
	}
	settings_->endGroup();

	settings_->beginGroup("aspect-angle-orb-diff");
	list = settings_->childKeys();
	BodyProps bp;
	bp.type = TYPE_ASPECT;
	for (int i = 0; i < list.size(); ++i) {
		QString name = list.at(i);
		int id = name.toInt();
		QStringList strList = settings_->value(name).toString().split(DELIMITER);
		double angle = strList[0].toDouble();
		double orb = strList[1].toDouble();
		int signDifference = strList[2].toInt();
		bp.userData = id;
		char angleChar = label(bp).toAscii()[0];
		AspectManager::get_mutable_instance().registerProps(
				id,angle, orb, signDifference, angleChar, angleChar);

	}
	settings_->endGroup();
}

void SettingsManager::fini()
{
	clearFonts(astrofont_);
	clearFonts(arialfont_);
	delete settings_;
}

QFont* SettingsManager::font(int size, font_face_t face) const
{
	QFont* fnt = NULL;
	const size_font_map& map = ((face == FF_ASTRO) ? astrofont_ : arialfont_).fonts_;
	size_font_map::const_iterator it = map.lower_bound(size);
	if (it != map.end())
		fnt = it->second;
	else
		fnt = map.rbegin()->second;
	return fnt;
}

void SettingsManager::clearFonts(font_glyph_t& font)
{
	for (size_font_map::iterator it = font.fonts_.begin(); it != font.fonts_.end(); ++it)
		delete (*it).second;
	font.fonts_.clear();
	font.planets_.clear();
	font.zodiac_signs_.clear();
}

void SettingsManager::loadFont(font_glyph_t& font, const QString& face)
{
	const int FONT_SIZES[] = {8, 9, 10, 11, 12, 13, 14, 16, 18, 22, 30, 36, 40, 48, 56, 60};
	clearFonts(font);
	for (int i = 0; i < sizeof(FONT_SIZES) / sizeof(FONT_SIZES[0]); ++i) {
		QFont* fnt = new QFont(face, FONT_SIZES[i]);
		font.fonts_[FONT_SIZES[i]] = fnt;
	}
	settings_->beginGroup("font-" + face);
	QStringList list = settings_->childKeys();
	for (int i = 0; i < list.size(); ++i) {
		QString name = list.at(i);
		int id = settings_->value(name).toInt();
		font.glyphs_[name] = id;
	}
	QString s = settings_->value("zodiac").toString();
	QStringList strList = s.split(DELIMITER);
	for (int i = 0; i < strList.size(); ++i) {
		font.zodiac_signs_.push_back(strList[i].toInt());
	}
	settings_->endGroup();
}

QString SettingsManager::label(const BodyProps& bp) const
{
	QString s(QString::number(bp.type) + "?");
	switch (bp.type) {
		case TYPE_ZODIAC:
			s.sprintf("%c", astrofont_.zodiac_signs_[bp.id]);
			break;
		case TYPE_PLANET: {
			std::map<int, QString>::const_iterator it = id2planet_.find(bp.id);
			if (it != id2planet_.end()) {
				std::map<QString, int>::const_iterator it1 = astrofont_.glyphs_.find((*it).second);
				if (it1 != astrofont_.glyphs_.end()) {
					char c = (*it1).second;
					s.sprintf("%c", c);
				}
			} }
			break;
		case TYPE_ASPECT: {
			std::map<QString, int>::const_iterator it1 = astrofont_.glyphs_.find(
					ASPECT_PREFIX + QString::number(bp.userData));
			if (it1 != astrofont_.glyphs_.end()) {
				char c = (*it1).second;
				s.sprintf("%c", c);
			} }
			break;
		case TYPE_HOUSE:
/*			switch ((astro_flag_t)) {
			case af_Asc:
				return "L";
			case af_IC:
				return "O";
			case af_Dsc:
				return "M";
			case af_MC:
				return "N";
			default:*/
			if (bp.flags & FLG_ARABIC)
				s = QString::number(bp.id - HOUSE_ID_FIRST + 1);
			else
				s = HOUSE_NAMES[bp.id - HOUSE_ID_FIRST];
			break;
			//}
	}
	return s;
}

QString SettingsManager::formulaVariable(const BodyProps& bp) const
{
	QString s("?");
	switch (bp.type) {
		case TYPE_PLANET: {
			std::map<int, QString>::const_iterator it = id2planet_.find(bp.id);
			if (it != id2planet_.end()) {
				s = (*it).second;
			} }
			break;
		case TYPE_HOUSE:
			s.sprintf("H%d", bp.id - HOUSE_ID_FIRST + 1);
			break;
	}
	return s;
}

char SettingsManager::degreeSign(font_face_t face) const
{
	if (face == FF_ASTRO)
		return '9' + 2;
	else
		return '`';
}

QString& SettingsManager::toBackTick(QString& str)
{
	return str.replace(DEG_STR, BACKTICK_STR);
}

QString& SettingsManager::fromBackTick(QString& str)
{
	return str.replace(BACKTICK_STR, DEG_STR);
}

const SettingsManager::StringPairVector& SettingsManager::houseMethodVec() const
{
	return house_method_;
}

QString SettingsManager::houseMethod() const
{
	return settings_->value("house_method", "P").toString();
}

void SettingsManager::setHouseMethod(const QString& str)
{
	settings_->setValue("house_method", str);
}

QString SettingsManager::aspectLabel(int id) const
{
	return "#";
}
