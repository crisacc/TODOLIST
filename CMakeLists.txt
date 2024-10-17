cmake_minimum_required(VERSION 3.20)
project(TODOLIST)

set(CMAKE_CXX_STANDARD 11)

add_executable(TODOLIST main.cpp
        Activity.cpp
        Activity.h
        TodoList.cpp
        TodoList.h)
