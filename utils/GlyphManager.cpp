#include "GlyphManager.h"
#include <QString>
#include <QSettings>
#include <QFont>

const QString DEG_STR("°");
const QString BACKTICK_STR("`");

void GlyphManager::init()
{
	settings_ = new QSettings("D:/prj/astronom-qt/settings/global.txt", QSettings::IniFormat);
	loadFont(astrofont_, "Astronom");
	loadFont(arialfont_, "Arial");
	settings_->beginGroup("ephemeris:mapping");
	QStringList list = settings_->childKeys();
	for (int i = 0; i < list.size(); ++i) {
		QString name = list.at(i);
		int id = settings_->value(name).toInt();
		planet2id_[name] = id;
		id2planet_[id] = name;
	}
}

void GlyphManager::fini()
{
	clearFonts(astrofont_);
	clearFonts(arialfont_);
	delete settings_;
}

QFont* GlyphManager::getFont(int size, font_face_t face) const
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

void GlyphManager::clearFonts(font_glyph_t& font)
{
	for (size_font_map::iterator it = font.fonts_.begin(); it != font.fonts_.end(); ++it)
		delete (*it).second;
	font.fonts_.clear();
	font.planets_.clear();
	font.zodiac_signs_.clear();
}

void GlyphManager::loadFont(font_glyph_t& font, const QString& face)
{
	const int FONT_SIZES[] = {8, 9, 10, 11, 12, 13, 14, 16, 18, 22, 30, 36, 40, 48, 56, 60};
	clearFonts(font);
	for (int i = 0; i < sizeof(FONT_SIZES) / sizeof(FONT_SIZES[0]); ++i) {
		QFont* fnt = new QFont(face, FONT_SIZES[i]);
		font.fonts_[FONT_SIZES[i]] = fnt;
	}
	settings_->beginGroup("font:" + face);
	QStringList list = settings_->childKeys();
	for (int i = 0; i < list.size(); ++i) {
		QString name = list.at(i);
		int id = settings_->value(name).toInt();
		font.glyphs_[name] = id;
	}
	const char DELIMITER = ' ';
	QString s = settings_->value("zodiac").toString();
	int space_count = s.count(DELIMITER);
	for (int i = 0; i <= space_count; ++i)
		font.zodiac_signs_.push_back(s.section(DELIMITER, i).toInt());
}

char GlyphManager::getLabel(body_type_t type, int id) const
{
	switch (type) {
		case TYPE_ZODIAC:
			return astrofont_.zodiac_signs_[id];
		case TYPE_PLANET: {
			std::map<int, QString>::const_iterator it = id2planet_.find(id);
			if (it != id2planet_.end()) {
				std::map<QString, int>::const_iterator it1 = astrofont_.glyphs_.find((*it).second);
				if (it1 != astrofont_.glyphs_.end())
				return (*it1).second;
			} }
		case TYPE_HOUSE:
			switch ((astro_flag_t)id) {
				case af_Asc:
					return 'L';
				case af_IC:
					return 'O';
				case af_Dsc:
					return 'M';
				case af_MC:
					return 'N';
			}
	}
	return '?';
}

char GlyphManager::getDegreeSign(font_face_t face) const
{
	if (face == FF_ASTRO)
		return '9' + 2;
	else
		return '`';
}

QString GlyphManager::getHouseLabel(int id, astro_flag_t af) const
{
	if (af == af_Undef)
		return QString(HOUSE_NAMES[id - HOUSE_ID_FIRST - 1]);
	QString s;
	s.sprintf("%c", getLabel(TYPE_HOUSE, (int)af));
	return s;
}

QString& GlyphManager::toBackTick(QString& str)
{
	return str.replace(DEG_STR, BACKTICK_STR);
}

QString& GlyphManager::fromBackTick(QString& str)
{
	return str.replace(BACKTICK_STR, DEG_STR);
}
