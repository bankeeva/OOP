cmake_minimum_required(VERSION 3.16)
project(csv)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_executable(csv
        main.cpp
        parser.h
        tuple_print.h
)

add_subdirectory(tests)