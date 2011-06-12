THD_PARTY = $$PWD/../3d_party
QT += sql
INCLUDEPATH += $$THD_PARTY/sweph/src $$THD_PARTY/boost_1_42_0 $$THD_PARTY/lua-5.1.4/src
LIBS += -L$$THD_PARTY/sweph/src -lswe -L$$THD_PARTY/lua-5.1.4/src -llua

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
    utils/DMS.cpp \
    utils/HouseProps.cpp \
    labels/HouseLabel.cpp \
    utils/Chart.cpp \
    models/PlanetSelectorFilterProxyModel.cpp \
    widgets/HouseSelectorDelegate.cpp \
    widgets/HouseSelector.cpp \
    models/HouseSelectorFilterProxyModel.cpp \
    widgets/BaseSelector.cpp \
    models/ModelHelper.cpp \
    utils/SettingsManager.cpp \
    forms/FormulaForm.cpp \
    utils/FormulaHelper.cpp \
    widgets/AsteroidSelector.cpp \
    models/AsteroidSelectorFilterProxyModel.cpp \
    widgets/BodySelector.cpp \
    widgets/BaseSelectorDelegate.cpp \
    widgets/BodySelectorDelegate.cpp \
    utils/convertors/BaseConvertor.cpp \
    utils/convertors/NatalConvertor.cpp \
    utils/validators/CoordValidator.cpp \
    widgets/CoordLineEdit.cpp \
    forms/PersonsForm.cpp \
    db/DBHelper.cpp \
    widgets/TimeOffsetEdit.cpp \
    utils/validators/TimeOffsetValidator.cpp \
    forms/ImportForm.cpp \
    db/ImportDBHelper.cpp

HEADERS += \
    forms/MainForm.h \
    utils/BodyProps.h \
    utils/Ephemeris.h \
    utils/TimeLoc.h \
    forms/InputForm.h \
    forms/GlyphForm.h \
    utils/constants.h \
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
    utils/DMS.h \
    utils/HouseProps.h \
    labels/HouseLabel.h \
    utils/Chart.h \
    models/PlanetSelectorFilterProxyModel.h \
    widgets/HouseSelectorDelegate.h \
    widgets/HouseSelector.h \
    models/HouseSelectorFilterProxyModel.h \
    widgets/BaseSelector.h \
    models/ModelHelper.h \
    utils/SettingsManager.h \
    forms/FormulaForm.h \
    utils/FormulaHelper.h \
    widgets/AsteroidSelector.h \
    models/AsteroidSelectorFilterProxyModel.h \
    widgets/BodySelector.h \
    widgets/BaseSelectorDelegate.h \
    widgets/BodySelectorDelegate.h \
    utils/convertors/BaseConvertor.h \
    utils/convertors/NatalConvertor.h \
    utils/validators/CoordValidator.h \
    widgets/CoordLineEdit.h \
    forms/PersonsForm.h \
    db/DBHelper.h \
    db/DBRecord.h \
    widgets/TimeOffsetEdit.h \
    utils/validators/TimeOffsetValidator.h \
    forms/ImportForm.h \
    models/ImportModelHelper.h \
    db/ImportDBHelper.h \
    db/Statements.h

FORMS += \
    forms/MainForm.ui \
    forms/InputForm.ui \
    forms/GlyphForm.ui \
    forms/form.ui \
    forms/FormulaForm.ui \
    forms/PersonsForm.ui \
    forms/ImportForm.ui

OTHER_FILES +=
