cmake_minimum_required(VERSION 3.10)

project(TestRemoveElement)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS} ${benchmark_INCLUDE_DIRS} /usr/local/benchmark/include/)
link_directories(/usr/local/benchmark/lib/)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(test_remove_element tests/test.cpp)

target_link_libraries(test_remove_element ${GTEST_LIBRARIES} ${benchmark_LIBRARIES} pthread benchmark)

add_test(NAME TestRemoveElement COMMAND test_remove_element)