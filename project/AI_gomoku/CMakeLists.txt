cmake_minimum_required(VERSION 3.16.3)

project(AI_CMake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O2 -g")

include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories($${CMAKE_SOURCE_DIR}/lib)

add_executable(ai_cmake main.cpp src/Man.cpp src/AI.cpp src/Chess.cpp src/ChessGame.cpp)

target_link_libraries(ai_cmake easyx)