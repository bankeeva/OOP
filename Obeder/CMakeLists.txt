cmake_minimum_required(VERSION 3.15)
project(Obeder)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include_directories(.)

add_executable(Obeder
        Obeder.h
        main.cpp
        ObederReceipt.h
        Obeder.cpp
        ObederReceipt.cpp)

add_subdirectory(test)
