cmake_minimum_required(VERSION 3.10)

project(FootbalSimulator)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(reader)
add_subdirectory(simulator)
add_executable(FootbalSimulator main.cpp)
target_link_libraries(FootbalSimulator reader simulator)