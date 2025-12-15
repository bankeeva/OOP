cmake_minimum_required(VERSION 3.16)

project(Tests)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

add_executable(test_csv
        test.cpp
        ../parser.h
        ../tuple_print.h
)

target_link_libraries(test_csv
        gtest
        gtest_main
)

add_test(NAME test_csv COMMAND test_csv)