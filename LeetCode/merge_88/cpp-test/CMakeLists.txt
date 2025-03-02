cmake_minimum_required(VERSION 3.10)

project(TestMerge)

# 手动指定 GTest 的路径
set(GTEST_ROOT /usr/local/opt/googletest)  # 根据实际路径修改

find_package(GTest REQUIRED)
include_directories(${GTEST_ROOT}/include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(test_merge tests/test.cpp)

target_link_libraries(test_merge ${GTEST_ROOT}/lib/libgtest.a ${GTEST_ROOT}/lib/libgtest_main.a pthread)

add_test(NAME TestMerge COMMAND test_merge)