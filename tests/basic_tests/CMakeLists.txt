add_executable(DateTest
        DateTests.cpp
)

add_executable(ActivityTest
        ActivityTests.cpp
)

add_executable(TodoListTest
        TodoListTests.cpp
)

target_link_libraries(DateTest PRIVATE GTest::gtest GTest::gtest_main TODOLIB)
target_link_libraries(ActivityTest PRIVATE GTest::gtest GTest::gtest_main TODOLIB)
target_link_libraries(TodoListTest PRIVATE GTest::gtest GTest::gtest_main TODOLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(../../TODOLIST/include)



add_test(NAME DateTests COMMAND DateTest)
add_test(NAME ActivityTests COMMAND ActivityTest)
add_test(NAME TodoListTests COMMAND TodoListTest)