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
    packagesmanager.cpp)

kconfig_add_kcfg_files(pak-gui pakGuiSettings.kcfgc)

target_link_libraries(pak-gui
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::ConfigWidgets
    KF5::DBusAddons
    KF5::Crash
    Qt5::Widgets
    Qt5::Concurrent
)

ki18n_wrap_ui(pak-gui
    mainwindowview.ui
    settings.ui)

install(FILES org.cachyos.pak-gui.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES pak-gui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/pak-gui)
install(TARGETS pak-gui ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
