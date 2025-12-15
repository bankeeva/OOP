cmake_minimum_required(VERSION 4.0)
project(task_0_a)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(task_0_a
        main.cpp
        module1.cpp
        module1.h
        module2.cpp
        module2.h
        module3.cpp
        module3.h)
