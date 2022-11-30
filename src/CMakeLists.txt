qt5_add_resources(RESOURCES ${CMAKE_SOURCE_DIR}/resources/pak-gui.qrc)

add_executable(pak-gui ${RESOURCES})

target_sources(pak-gui PRIVATE
    main.cpp
    mainwindow.cpp
    mainwindowview.cpp
    availablepackagescolumn.cpp
    updatedpackagescolumn.cpp
    installedpackagescolumn.cpp
    packagescolumn.h
    qipackage.cpp
    sipackage.cpp
    checkpackage.cpp
    defs.h
    package.h
    commandparser.h
    sicommandparser.cpp
    qicommandparser.cpp
    checkcommandparser.cpp
    progressview.cpp
    statisticscommandparser.cpp
    statisticscommandparser.h
    searchallcommandparser.cpp
    searchallcommandparser.h
    downloadcommandparser.cpp
    downloadcommandparser.h
    statistics.cpp
    statistics.h
    process.cpp
    process.h
    packageinputwindow.cpp
    packageinputwindow.h
    packagedownloader.cpp
    packagedownloader.h
    choicewindow.cpp
    choicewindow.h
    outputfilter.cpp
    outputfilter.h
    sorter.cpp
    sorter.h
    actionsaccesschecker.cpp
    actionsaccesschecker.h
    settings.cpp
    settings.h
    logger.cpp
    logger.h
    previewdesign.cpp
    previewdesign.h
    timeconverter.cpp
    timeconverter.h
    sizeconverter.cpp
    sizeconverter.h
    pathconverter.cpp
    pathconverter.h
    spinninganimation.cpp
    spinninganimation.h
    systemtray.cpp
    systemtray.h
    settingsrecords.cpp
    settingsrecords.h)

kconfig_add_kcfg_files(pak-gui pakGuiSettings.kcfgc)

target_link_libraries(pak-gui
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::ConfigWidgets
    KF5::DBusAddons
    KF5::Crash
    KF5::Notifications
    Qt5::Widgets
    Qt5::Charts
    Qt5::Concurrent
    Qt5::Network
)

ki18n_wrap_ui(pak-gui
    mainwindowview.ui
    generalsettings.ui
    progressview.ui
    packageinput.ui
    choicewindow.ui
    previewsappearancesettings.ui
    packagesinfosettings.ui
    logssettings.ui)

install(FILES org.cachyos.pak-gui.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES pak-gui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/pak-gui)
install(TARGETS pak-gui ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
