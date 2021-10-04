#Following youtube video "https://www.youtube.com/watch?v=Lp1ifh9TuFI"

cmake_minimum_required(VERSION 3.8)

set(This Train)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing() ##let's cmake know we are using unit test

add_subdirectory(googletest)

set(Headers 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include/merge_sort.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include/dijkstra.h
)
set(Sources 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/merge_sort.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dijkstra.cpp
)

# this will link with other things to run programs
# Note: googletest will be the program and our code will be the library
add_library(${This} STATIC ${Sources} ${Headers})

# create a test sub directory to keep test separate from code
# It will also run a cmake inside that directory
add_subdirectory(test)