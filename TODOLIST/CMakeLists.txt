add_library(TODOLIB
        Activity.cpp
        TodoList.cpp
        Date.cpp
)

include_directories(include)

target_include_directories(TODOLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
