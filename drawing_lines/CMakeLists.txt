cmake_minimum_required(VERSION 3.26)
project(drawing_lines)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(.)

add_executable(drawing_lines
        main.cpp
        BitmapPlusPlus.hpp
        img.h
        img.cpp)

add_subdirectory(test) #
