cmake_minimum_required(VERSION 3.5)
project(pak-gui-tests VERSION 0.1 LANGUAGES CXX)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6Test REQUIRED)
else()
    find_package(Qt5Test REQUIRED)
endif()

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(PAK_TESTS_SOURCES tests.cpp)

add_executable(pak-tests ${PAK_TESTS_SOURCES})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    target_link_libraries( pak-tests  GTest::gtest GTest::gtest_main Qt6::Test )
else()
    target_link_libraries( pak-tests  GTest::gtest GTest::gtest_main Qt5::Test )
endif()

ADD_TEST( NAME pak-tests  COMMAND pak-tests  )
