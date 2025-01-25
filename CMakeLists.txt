cmake_minimum_required(VERSION 3.28)

set(CMAKE_GENERATOR "MinGW Makefiles")
set(SRC_F
    ./source/main.cpp
    ./source/mechanics/rand.cpp
    ./source/mechanics/score_table.cpp
)

project(hw03 LANGUAGES CXX)
add_executable(otus-cpp-basics-hw03 ${SRC_F})