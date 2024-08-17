cmake_minimum_required(VERSION 3.14)
project(practice_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(practice_cpp main.cpp)

find_package(GTest CONFIG REQUIRED)

include_directories(./)

add_executable(practice_test advanced_cpp20_programming/type_and_object/type_inference.cpp
        advanced_cpp20_programming/type_and_object/value_categroy.cpp)

target_link_libraries(practice_test GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
