cmake_minimum_required(VERSION 3.20)
project(TODOLIST)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(TODOLIST)

add_subdirectory(tests)

include_directories(include)

add_executable(TODOLIST main.cpp)
