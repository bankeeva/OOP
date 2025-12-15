cmake_minimum_required(VERSION 3.15)
project(coin_collecting_robots)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include_directories(.)

add_executable(coin_collecting_robots
        main.cpp
        Field.h
        Field.cpp
        Strategy.h
        RandomVHStrategy.h
        RandomDStrategy.h
        GreedyStrategy.h
        LadderStrategy.h
        BounceStrategy.h
)

add_subdirectory(test)

include_directories(.)
