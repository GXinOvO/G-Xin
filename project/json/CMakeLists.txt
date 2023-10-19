cmake_minimum_required(VERSION 3.16.3)

project(json_cmake)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(main_cmake main.c src/leptjson.c)