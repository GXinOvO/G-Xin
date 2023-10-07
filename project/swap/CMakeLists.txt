cmake_minimum_required(VERSION 3.16.3)

project(SWAP_CMAKE)

include_directories(include)

add_executable(main_cmake main.cpp src/swap.cpp)