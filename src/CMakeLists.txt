qt5_add_resources(RESOURCES ${CMAKE_SOURCE_DIR}/resources/pak-gui.qrc)

add_executable(pak-gui ${RESOURCES})

target_sources(pak-gui PRIVATE
    main.cpp
    src/algorithms.cpp
    src/algorithms.h
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindowview.cpp
    src/mainwindowview.h
    src/mainwindowviewsignals.cpp
    src/mainwindowviewsignals.h
    src/availablepackagescolumn.cpp
    src/availablepackagescolumn.h
    src/updatedpackagescolumn.cpp
    src/updatedpackagescolumn.h
    src/installedpackagescolumn.cpp
    src/installedpackagescolumn.h
    src/packagescolumn.h
    src/packagescolumn.cpp
    src/qipackage.cpp
    src/qipackage.h
    src/sipackage.cpp
    src/sipackage.h
    src/checkpackage.cpp
    src/checkpackage.h
    src/defs.h
    src/defs.cpp
    src/package.h
    src/package.cpp
    src/commandparser.h
    src/sicommandparser.cpp
    src/sicommandparser.h
    src/qicommandparser.cpp
    src/qicommandparser.h
    src/checkcommandparser.cpp
    src/checkcommandparser.h
    src/progressview.cpp
    src/progressview.h
    src/statisticscommandparser.cpp
    src/statisticscommandparser.h
    src/searchallcommandparser.cpp
    src/searchallcommandparser.h
    src/downloadcommandparser.cpp
    src/downloadcommandparser.h
    src/installcommandparser.cpp
    src/installcommandparser.h
    src/statistics.cpp
    src/statistics.h
    src/process.cpp
    src/process.h
    src/packageinputwindow.cpp
    src/packageinputwindow.h
    src/packagedownloader.cpp
    src/packagedownloader.h
    src/packagesearch.cpp
    src/packagesearch.h
    src/choicewindow.cpp
    src/choicewindow.h
    src/outputfilter.cpp
    src/outputfilter.h
    src/sorter.cpp
    src/sorter.h
    src/actionsaccesschecker.cpp
    src/actionsaccesschecker.h
    src/settings.cpp
    src/settings.h
    src/logger.cpp
    src/logger.h
    src/previewdesign.cpp
    src/previewdesign.h
    src/timeconverter.cpp
    src/timeconverter.h
    src/sizeconverter.cpp
    src/sizeconverter.h
    src/pathconverter.cpp
    src/pathconverter.h
    src/spinninganimation.cpp
    src/spinninganimation.h
    src/systemtray.cpp
    src/systemtray.h
    src/settingsrecords.cpp
    src/settingsrecords.h)

kconfig_add_kcfg_files(pak-gui src/pakGuiSettings.kcfgc)

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
    src/mainwindowview.ui
    src/generalsettings.ui
    src/progressview.ui
    src/packageinput.ui
    src/choicewindow.ui
    src/previewsappearancesettings.ui
    src/packagesinfosettings.ui
    src/logssettings.ui)

install(FILES src/org.cachyos.pak-gui.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES src/pak-gui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/pak-gui)
install(TARGETS pak-gui ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
