cmake_minimum_required(VERSION 3.28)
project(HW4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(HW4
        main.cpp
        avl-tree.h)
