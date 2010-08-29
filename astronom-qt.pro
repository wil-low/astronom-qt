THD_PARTY = $$PWD/../3d_party
INCLUDEPATH += $$THD_PARTY/sweph/src $$THD_PARTY/boost_1_42_0
LIBS += -L$$THD_PARTY/sweph/src -lswe

TRANSLATIONS = \
	astronom_ru.ts \
	astronom_uk.ts

SOURCES += \
    main.cpp \
    forms/MainForm.cpp \
    widgets/AstroLabel.cpp \
    widgets/AspectLabel.cpp \
    models/PlanetModel.cpp \
    utils/BodyProps.cpp \
    utils/Ephemeris.cpp \
    utils/TimeLoc.cpp \
    forms/InputForm.cpp \
    forms/GlyphForm.cpp

HEADERS += \
    forms/MainForm.h \
    widgets/AstroLabel.h \
    widgets/AspectLabel.h \
    models/PlanetModel.h \
    utils/BodyProps.h \
    utils/Ephemeris.h \
    utils/TimeLoc.h \
    forms/InputForm.h \
    forms/GlyphForm.h

FORMS += \
    forms/MainForm.ui \
    forms/InputForm.ui \
    forms/GlyphForm.ui

OTHER_FILES +=
