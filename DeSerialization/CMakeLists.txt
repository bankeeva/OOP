cmake_minimum_required(VERSION 3.15)
project(DeSerialization)

set(CMAKE_CXX_STANDARD 17)

add_library(serialize_lib
        serialize.cpp
        serialize.h)

add_subdirectory(test)
