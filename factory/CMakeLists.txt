cmake_minimum_required(VERSION 4.0)
project(factory)

set(CMAKE_CXX_STANDARD 14)

add_executable(factory
        main.cpp
        object.cpp
        object.h
        point.h
        rect.h
        line.h
        circle.h
        tests/test.cpp
)

enable_testing()

include_directories(./)

add_executable(tests
        test.cpp
object.cpp)
target_link_libraries(tests gtest_main)
