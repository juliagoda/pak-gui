cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")

set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

project(pak-gui VERSION ${VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic")

set(QT_MIN_VERSION "5.12.8")
set(KF_MIN_VERSION "5.68.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/packages")

include(ECMInstallIcons)
include(ECMSetupVersion)
include(ECMOptionalAddSubdirectory)
include(GenerateExportHeader)
include(ECMAddAppIcon)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(ECMAddTests)
include(ECMAddAppIcon)
include(CMakePackageConfigHelpers)
include(ECMSetupQtPluginMacroNames)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)

option(RUN_TESTS "Allow tests for classes" OFF)

if(RUN_TESTS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

find_package(pak REQUIRED)
find_package(pacman-contrib REQUIRED)
find_package(kdesu REQUIRED)
find_package(ksshaskpass REQUIRED)
find_package(bash REQUIRED)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets Charts Concurrent Network)

find_package(Git)
find_package(devtools)
find_package(auracle)
find_package(namcap)
find_package(reflector)
find_package(subversion)
find_package(fzf)
find_package(downgrade)
find_package(libnotify)

if(RUN_TESTS)
    add_definitions(-DRUN_TESTS)
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

install(PROGRAMS com.github.juliagoda.pak-gui.desktop DESTINATION ${KDE_INSTALL_APPDIR})

include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(resources)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

if(RUN_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(RUN_TESTS)
