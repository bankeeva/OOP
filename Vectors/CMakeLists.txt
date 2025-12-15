cmake_minimum_required(VERSION 4.0)
project(Vectors)

set(CMAKE_CXX_STANDARD 14)

enable_testing() #

include_directories(.)

add_executable(Vectors
        Vector.cpp)

add_subdirectory(../drawing_lines/test) #
