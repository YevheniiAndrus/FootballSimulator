cmake_minimum_required(VERSION 3.10)

project(CSV_READER)
set(HEADERS reader.h)
set(SOURCE reader.cpp)

add_library(reader ${SOURCE} ${HEADERS})