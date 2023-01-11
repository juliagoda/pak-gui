cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(pak-gui VERSION 1.0.0 LANGUAGES CXX)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(QT_MIN_VERSION "5.12.8")
set(KF_MIN_VERSION "5.68.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/packages")

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMInstallIcons)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)

option(RUN_TESTS "Allow tests for classes" OFF)
find_package(pak REQUIRED)
find_package(pacman-contrib REQUIRED)
find_package(kdesu REQUIRED)
find_package(ksshaskpass REQUIRED)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets Charts Concurrent Network)

find_package(Git)
find_package(asp)
find_package(auracle-git)
find_package(namcap)
find_package(reflector)
find_package(subversion)
find_package(fzf)
find_package(downgrade)
find_package(libnotify)

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
    Notifications)

#find_package(Qt5 REQUIRED COMPONENTS Concurrent Network)

install(PROGRAMS org.cachyos.pak-gui.desktop DESTINATION ${KDE_INSTALL_APPDIR})

include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(resources)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

if(RUN_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(RUN_TESTS)
