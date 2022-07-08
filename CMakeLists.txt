cmake_minimum_required(VERSION 3.5)

project(pak-gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# search packages used by KDE
find_package(ECM 1.3.0 REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}/modules" ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(KF5 REQUIRED COMPONENTS DocTools CoreAddons)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(RUN_TESTS "Allow tests for classes" ON)

if(RUN_TESTS)
    message("Tests enabled")
endif(RUN_TESTS)

set(TS_FILES pak-qt_en_US.ts)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        ui/mainwindow.ui
        resources/translations/${TS_FILES})

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/ui)

add_executable(pak-gui ${PROJECT_SOURCES})
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(pak-gui PRIVATE Qt5::Widgets KF5::CoreAddons KF5::DocTools)

install(
   TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(
   FILES pak-gui.desktop
   DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

install(
   FILES pak-gui.png
   DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps)

if(RUN_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(RUN_TESTS)
