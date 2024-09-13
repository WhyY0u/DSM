cmake_minimum_required(VERSION 3.10)
project(DSM VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/**/*.cpp")

set(MAIN_SOURCE "src/Main.cpp")

list(APPEND SOURCES ${MAIN_SOURCE})

add_executable(DSM ${SOURCES})
