cmake_minimum_required(VERSION 3.10)

project(Simulator)
set(HEADERS simulator.h)
set(SOURCE simulator.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_library(simulator ${SOURCE} ${HEADERS})

add_subdirectory(../googletest googletest)
add_executable(tests unit_tests/simulator_tests.cpp)
target_link_libraries(tests gtest gtest_main simulator)