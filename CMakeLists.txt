cmake_minimum_required(VERSION 3.20)
project(TODOLIST)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(TODOLIST)

add_subdirectory(tests)

add_executable(TODOLIST main.cpp)
