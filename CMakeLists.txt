cmake_minimum_required(VERSION 3.10)
project(DSM VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/**/*.cpp")
file(GLOB_RECURSE HEADER_DIRS LIST_DIRECTORIES true "src/**/*.h")

set(MAIN_SOURCE "src/Main.cpp")

list(APPEND SOURCES ${MAIN_SOURCE})

foreach(header_dir ${HEADER_DIRS})
    get_filename_component(header_path ${header_dir} DIRECTORY)
    include_directories(${header_path})
endforeach()

add_executable(DSM ${SOURCES})


