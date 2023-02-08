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

target_include_directories(pak-gui-src  PUBLIC ${CMAKE_SOURCE_DIR}/src/src)
add_executable(pak-tests ${CMAKE_SOURCE_DIR}/tests/main.cpp ${CMAKE_SOURCE_DIR}/tests/tests.cpp ${CMAKE_SOURCE_DIR}/tests/settings.cpp ${CMAKE_SOURCE_DIR}/tests/gui/packagescolumnfixtures.h ${MY_APP_SRC} ${MY_APP_HEADERS} ${MY_APP_UI} ${RESOURCES})
add_executable(installed-packages-column ${CMAKE_SOURCE_DIR}/tests/gui/installedpackagescolumn.cpp  ${CMAKE_SOURCE_DIR}/tests/gui/packagescolumnfixtures.h ${MY_APP_SRC} ${MY_APP_HEADERS} ${MY_APP_UI} ${RESOURCES})
add_executable(available-packages-column ${CMAKE_SOURCE_DIR}/tests/gui/availablepackagescolumn.cpp  ${CMAKE_SOURCE_DIR}/tests/gui/packagescolumnfixtures.h ${MY_APP_SRC} ${MY_APP_HEADERS} ${MY_APP_UI} ${RESOURCES})
add_executable(packages-to-update-column ${CMAKE_SOURCE_DIR}/tests/gui/packagestoupdatecolumn.cpp  ${CMAKE_SOURCE_DIR}/tests/gui/packagescolumnfixtures.h ${MY_APP_SRC} ${MY_APP_HEADERS} ${MY_APP_UI} ${RESOURCES})
add_executable(settings-window ${CMAKE_SOURCE_DIR}/tests/gui/settings.cpp  ${CMAKE_SOURCE_DIR}/tests/gui/packagescolumnfixtures.h ${MY_APP_SRC} ${MY_APP_HEADERS} ${MY_APP_UI} ${RESOURCES})
add_executable(main-window ${CMAKE_SOURCE_DIR}/tests/gui/mainwindow.cpp  ${CMAKE_SOURCE_DIR}/tests/gui/packagescolumnfixtures.h ${MY_APP_SRC} ${MY_APP_HEADERS} ${MY_APP_UI} ${RESOURCES})
add_test(NAME mainwindow-gui COMMAND mainwindow-gui)

target_link_libraries(pak-tests
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

target_link_libraries(installed-packages-column
    GTest::gtest
    GTest::gtest_main
    KF5::CoreAddons
    Qt5::Test
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    pak-gui-src
)

target_link_libraries(available-packages-column
    GTest::gtest
    GTest::gtest_main
    KF5::CoreAddons
    Qt5::Test
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    pak-gui-src
)

target_link_libraries(packages-to-update-column
    GTest::gtest
    GTest::gtest_main
    KF5::CoreAddons
    Qt5::Test
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    pak-gui-src
)

target_link_libraries(main-window
    GTest::gtest
    GTest::gtest_main
    KF5::CoreAddons
    Qt5::Test
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    pak-gui-src
)

target_link_libraries(settings-window
    GTest::gtest
    GTest::gtest_main
    KF5::CoreAddons
    Qt5::Test
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    pak-gui-src
)
