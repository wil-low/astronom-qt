THD_PARTY = $$PWD/../3d_party
INCLUDEPATH += $$THD_PARTY/sweph/src $$THD_PARTY/boost_1_42_0
LIBS += -L$$THD_PARTY/sweph/src -lswe

TRANSLATIONS = \
	astronom_ru.ts \
	astronom_uk.ts

SOURCES += \
    main.cpp \
    forms/MainForm.cpp \
    widgets/AspectLabel.cpp \
    models/PlanetModel.cpp \
    utils/BodyProps.cpp \
    utils/Ephemeris.cpp \
    utils/TimeLoc.cpp \
    forms/InputForm.cpp \
    forms/GlyphForm.cpp \
    utils/GlyphManager.cpp \
    views/DraggableGraphicsView.cpp \
    utils/DrawHelper.cpp \
    views/OcularView.cpp \
    labels/AstroLabelContainer.cpp \
    labels/AstroLabel.cpp \
    labels/ZodiacLabel.cpp \
    CircleSpread/CircleSpread.cpp

HEADERS += \
    forms/MainForm.h \
    widgets/AspectLabel.h \
    models/PlanetModel.h \
    utils/BodyProps.h \
    utils/Ephemeris.h \
    utils/TimeLoc.h \
    forms/InputForm.h \
    forms/GlyphForm.h \
    utils/constants.h \
    utils/GlyphManager.h \
    views/DraggableGraphicsView.h \
    utils/DrawHelper.h \
    views/OcularView.h \
    labels/AstroLabelContainer.h \
    labels/AstroLabel.h \
    labels/ZodiacLabel.h \
    CircleSpread/CircleSpread.h

FORMS += \
    forms/MainForm.ui \
    forms/InputForm.ui \
    forms/GlyphForm.ui

OTHER_FILES +=
