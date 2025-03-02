cmake_minimum_required(VERSION 3.10)

project(TestRemoveElement)

set(GTEST_ROOT /usr/local/opt/googletest)  # 根据实际路径修改

# 使用 find_package 查找 GTest 和 Benchmark
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

include_directories(${GTEST_ROOT}/include ${benchmark_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(test_remove_element tests/test.cpp)

# 确保链接 GTest 和 Benchmark 库
target_link_libraries(test_remove_element ${GTEST_ROOT}/lib/libgtest.a ${GTEST_ROOT}/lib/libgtest_main.a benchmark::benchmark pthread)

add_test(NAME TestRemoveElement COMMAND test_remove_element)