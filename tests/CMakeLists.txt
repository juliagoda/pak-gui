cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(pak-gui-tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_MIN_VERSION "5.12.8")
set(KF_MIN_VERSION "5.68.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} "${CMAKE_SOURCE_DIR}/packages")

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(pak REQUIRED)
find_package(pacman-contrib REQUIRED)
find_package(kdesu REQUIRED)
find_package(ksshaskpass REQUIRED)

find_package(Git)
find_package(asp)
find_package(auracle-git)
find_package(namcap)
find_package(reflector)
find_package(subversion)
find_package(fzf)
find_package(downgrade)
find_package(libnotify)

find_package(KF5 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    ConfigWidgets
    CoreAddons
    Crash
    DBusAddons
    DocTools
    I18n
    XmlGui
    Notifications
)

qt5_add_resources(RESOURCES ${CMAKE_SOURCE_DIR}/resources/pak-gui.qrc)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets Charts Concurrent Network)

include_directories(${GTEST_INCLUDE_DIRS})
file(GLOB_RECURSE MY_APP_SRC ${CMAKE_SOURCE_DIR}/src/src/*.cpp)
file(GLOB_RECURSE MY_APP_HEADERS ${CMAKE_SOURCE_DIR}/src/src/*.h)
file(GLOB_RECURSE MY_APP_UI ${CMAKE_SOURCE_DIR}/src/src/*.ui)
kconfig_add_kcfg_files(pak-gui-src ${CMAKE_SOURCE_DIR}/src/src/pakGuiSettings.kcfgc)

ki18n_wrap_ui(pak-gui-src
    ${MY_APP_UI})

add_library(pak-gui-src ${MY_APP_SRC} ${MY_APP_HEADERS} ${MY_APP_UI} ${RESOURCES})

target_link_libraries(pak-gui-src
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::ConfigWidgets
    KF5::DBusAddons
    KF5::Crash
    KF5::Notifications
    KF5::DocTools
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Charts
    Qt5::Concurrent
    Qt5::Network
)

target_include_directories(pak-gui-src PUBLIC ${CMAKE_SOURCE_DIR}/src/src)

add_executable(pak-gtests
    ${CMAKE_SOURCE_DIR}/tests/main.cpp
    ${CMAKE_SOURCE_DIR}/tests/tests.cpp
    ${CMAKE_SOURCE_DIR}/tests/settings.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/packagescolumnfixtures.h
    ${MY_APP_SRC} ${MY_APP_HEADERS}
    ${MY_APP_UI}
    ${RESOURCES})

add_executable(pak-qtests
    ${CMAKE_SOURCE_DIR}/tests/gui/main.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/installedpackagescolumntest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/installedpackagescolumntest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/availablepackagescolumntest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/availablepackagescolumntest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/packagestoupdatecolumntest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/packagestoupdatecolumntest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/settingstest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/settingstest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/mainwindowtest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/mainwindowtest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/actionsaccesscheckertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/actionsaccesscheckertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/checkcommandparsertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/checkcommandparsertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/checkpackagetest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/checkpackagetest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/downloadcommandparsertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/downloadcommandparsertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/installcommandparsertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/installcommandparsertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/loggertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/loggertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/checkcommandparsertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/checkcommandparsertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/checkpackagetest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/checkpackagetest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/choicewindowtest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/choicewindowtest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/downloadcommandparsertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/downloadcommandparsertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/installcommandparsertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/installcommandparsertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/loggertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/loggertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/outputfiltertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/outputfiltertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/packagedownloadertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/packagedownloadertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/packageinputwindowtest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/packageinputwindowtest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/packagesearchtest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/packagesearchtest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/pathconvertertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/pathconvertertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/previewdesigntest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/previewdesigntest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/processtest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/processtest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/progressviewtest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/progressviewtest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/qicommandparsertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/qicommandparsertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/qipackagetest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/qipackagetest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/searchallcommandparsertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/searchallcommandparsertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/sicommandparsertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/sicommandparsertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/sipackagetest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/sipackagetest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/sizeconvertertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/sizeconvertertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/statisticswindowtesttest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/statisticswindowtesttest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/statisticscommandparsertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/statisticscommandparsertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/systemtraytest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/systemtraytest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/timeconvertertest.cpp
    ${CMAKE_SOURCE_DIR}/tests/gui/timeconvertertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/timeconvertertest.h
    ${CMAKE_SOURCE_DIR}/tests/gui/defstest.h
    ${MY_APP_SRC}
    ${MY_APP_HEADERS}
    ${MY_APP_UI}
    ${RESOURCES}
)

target_link_libraries(pak-gtests
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
    KF5::CoreAddons
    Qt5::Test
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    pak-gui-src
)

target_link_libraries(pak-qtests
    KF5::CoreAddons
    Qt5::Test
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    pak-gui-src
)

