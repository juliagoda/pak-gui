cmake_minimum_required(VERSION 3.16)

project(pak-gui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_MIN_VERSION "5.15.0")
set(KF_MIN_VERSION "5.68.0)

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMInstallIcons)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)

option(RUN_TESTS "Allow tests for classes" OFF)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets)

if(RUN_TESTS)
    message("Tests enabled")
endif(RUN_TESTS)

find_package(KF5 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    ConfigWidgets
    CoreAddons
    Crash
    DBusAddons
    DocTools
    I18n
    XmlGui
)

install(PROGRAMS org.example.pak-gui.desktop  DESTINATION ${KDE_INSTALL_APPDIR})

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/ui)

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(resources)


# Make it possible to use the po files fetched by the fetch-translations step
ki18n_install(po)
kdoctools_install(po)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

if(RUN_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(RUN_TESTS)
