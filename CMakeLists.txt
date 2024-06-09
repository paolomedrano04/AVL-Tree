cmake_minimum_required(VERSION 3.28)
project(HW3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(HW3
        main.cpp
        hash_table.h)
