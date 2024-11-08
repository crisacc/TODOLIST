add_library(TODOLIB
        Activity.cpp
        TodoList.cpp
        Activity.cpp
)

target_include_directories(TODOLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
