cmake_minimum_required(VERSION 3.26)
project(cpp_five_in_a_row)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_five_in_a_row main.cpp
        src/Game.h
        src/Game.cpp
)
