cmake_minimum_required(VERSION 3.10)

project(ArringoTest)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(reader)
add_subdirectory(simulator)
add_executable(ArringoTest main.cpp)
target_link_libraries(ArringoTest reader simulator)