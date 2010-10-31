THD_PARTY = $$PWD/../3d_party
INCLUDEPATH += $$THD_PARTY/sweph/src $$THD_PARTY/boost_1_42_0
LIBS += -L$$THD_PARTY/sweph/src -lswe

TRANSLATIONS = \
	astronom_ru.ts \
	astronom_uk.ts

SOURCES += \
    main.cpp \
    forms/MainForm.cpp \
    utils/BodyProps.cpp \
    utils/Ephemeris.cpp \
    utils/TimeLoc.cpp \
    forms/InputForm.cpp \
    forms/GlyphForm.cpp \
    utils/GlyphManager.cpp \
    utils/DrawHelper.cpp \
    views/OcularView.cpp \
    labels/AstroLabelContainer.cpp \
    labels/AstroLabel.cpp \
    labels/ZodiacLabel.cpp \
    CircleSpread/CircleSpread.cpp \
    models/OcularDelegate.cpp \
    labels/PlanetLabel.cpp \
    labels/LabelFactory.cpp \
    widgets/PlanetSelector.cpp \
    widgets/PlanetSelectorDelegate.cpp \
    utils/DMS.cpp \
    utils/HouseProps.cpp \
    labels/HouseLabel.cpp

HEADERS += \
    forms/MainForm.h \
    utils/BodyProps.h \
    utils/Ephemeris.h \
    utils/TimeLoc.h \
    forms/InputForm.h \
    forms/GlyphForm.h \
    utils/constants.h \
    utils/GlyphManager.h \
    utils/DrawHelper.h \
    views/OcularView.h \
    labels/AstroLabelContainer.h \
    labels/AstroLabel.h \
    labels/ZodiacLabel.h \
    CircleSpread/CircleSpread.h \
    models/OcularDelegate.h \
    labels/PlanetLabel.h \
    labels/LabelFactory.h \
    widgets/PlanetSelector.h \
    widgets/PlanetSelectorDelegate.h \
    utils/DMS.h \
    utils/HouseProps.h \
    labels/HouseLabel.h

FORMS += \
    forms/MainForm.ui \
    forms/InputForm.ui \
    forms/GlyphForm.ui \
    forms/form.ui

OTHER_FILES +=
