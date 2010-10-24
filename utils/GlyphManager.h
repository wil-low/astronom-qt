#pragma once
#include <map>
#include <boost/serialization/singleton.hpp>
#include "../utils/constants.h"
#include <vector>
#include <QStringList>

class QString;
class QFont;
class QSettings;

class GlyphManager : public boost::serialization::singleton<GlyphManager>
{
public:
	void init();
	void fini();

	char label(body_type_t type, int id) const;
	char name(body_type_t type, int id) const;
	char degreeSign(font_face_t face) const;
	QString houseLabel(int id, astro_flag_t hf) const;

	QFont* font(int size, font_face_t face) const;
	static QString& toBackTick (QString& str);
	static QString& fromBackTick (QString& str);
private:
	typedef std::map<int, QFont*> size_font_map;
	struct font_glyph_t {
		size_font_map fonts_;
		std::map<QString, int> glyphs_;
		std::map<int, int> planets_;
		std::vector<int> zodiac_signs_;
	};
	std::map<QString, int> planet2id_;
	std::map<int, QString> id2planet_;
	void clearFonts(font_glyph_t& font);
	void loadFont(font_glyph_t& font, const QString& face);
	font_glyph_t astrofont_;
	font_glyph_t arialfont_;
	QSettings* settings_;
};
