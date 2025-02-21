cmake_minimum_required(VERSION 3.10)

project(TestMerge)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(test_merge tests/test.cpp)

target_link_libraries(test_merge ${GTEST_LIBRARIES} pthread)

add_test(NAME TestMerge COMMAND test_merge)