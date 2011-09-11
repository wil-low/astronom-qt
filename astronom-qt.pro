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
	db/ImportDBHelper.cpp \
    views/SpeculumView.cpp \
    views/items/SpeculumCell.cpp \
    labels/AspectLabel.cpp \
    utils/CRC32.cpp \
    views/CentralView.cpp \
    views/items/SpeculumHorizHeader.cpp \
    views/items/SpeculumVertHeader.cpp \
    labels/ReferenceLabel.cpp \
    widgets/QtCreator/utils/stylehelper.cpp \
    widgets/QtCreator/fancytabwidget.cpp \
    widgets/QtCreator/utils/styledbar.cpp \
    widgets/DocumentWidget.cpp \
    utils/DocumentManager.cpp \
    utils/Aspect.cpp \
    utils/AspectProps.cpp \
    models/AspectModelHelper.cpp \
    utils/AspectManager.cpp \
    widgets/Aspectarium.cpp

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
    widgets/TimeOffsetEdit.h \
    utils/validators/TimeOffsetValidator.h \
    forms/ImportForm.h \
    db/ImportDBHelper.h \
	db/Statements.h \
    views/SpeculumView.h \
    views/items/SpeculumCell.h \
    labels/AspectLabel.h \
    utils/CRC32.h \
    views/CentralView.h \
    views/items/SpeculumHorizHeader.h \
    views/items/SpeculumVertHeader.h \
    labels/ReferenceLabel.h \
    utils/css.h \
    views/colors/OcularColors.h \
    views/colors/SpeculumColors.h \
    views/items/SpeculumConst.h \
    widgets/QtCreator/utils/stylehelper.h \
    widgets/QtCreator/utils/utils_global.h \
    widgets/QtCreator/fancytabwidget.h \
    widgets/QtCreator/utils/styledbar.h \
    widgets/DocumentWidget.h \
    utils/DocumentManager.h \
    utils/Aspect.h \
    utils/AspectProps.h \
    models/AspectModelHelper.h \
    utils/AspectManager.h \
    widgets/Aspectarium.h

FORMS += \
    forms/MainForm.ui \
    forms/InputForm.ui \
    forms/GlyphForm.ui \
    forms/form.ui \
    forms/FormulaForm.ui \
    forms/PersonsForm.ui \
    forms/ImportForm.ui

OTHER_FILES +=
