cmake_minimum_required(VERSION 3.16.3)

project(Soldier_cmake)

# include_directories(./include)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

set(CMAKE_BUILD_TYPE Debug)

add_executable(main_cmake main.cpp src/Gun.cpp src/Soldier.cpp)

