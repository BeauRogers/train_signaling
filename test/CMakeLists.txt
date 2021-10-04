cmake_minimum_required(VERSION 3.8)

set(This TrainTests)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(Source
    TrainTests.cpp
)

add_executable(${This} ${Source})

target_link_libraries(${This} PUBLIC
    gtest_main
    Train
)

add_test(
    NAME ${This}
    COMMAND ${This}
)