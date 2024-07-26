cmake_minimum_required(VERSION 3.14)
project(practice_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(practice_cpp main.cpp)

find_package(GTest REQUIRED)

add_executable(practice_test type_inference.cpp)

target_link_libraries(practice_test GTest::GTest GTest::Main)

