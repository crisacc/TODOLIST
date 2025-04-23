# Aggiungi la libreria TODOLIB
add_library(TODOLIB
        ../../TODOLIST/Activity.cpp
        ../../TODOLIST/Date.cpp
        ../../TODOLIST/TodoList.cpp
)

# Assicurati che il codice di testing includa anche i file header di TODOLIB
target_include_directories(TODOLIB PUBLIC ../../TODOLIST/include)

# Ora collega TODOLIB nei test
add_executable(DateTest
        DateTests.cpp
)
target_link_libraries(DateTest PRIVATE GTest::gtest GTest::gtest_main TODOLIB)

add_executable(ActivityTest
        ActivityTests.cpp
)
target_link_libraries(ActivityTest PRIVATE GTest::gtest GTest::gtest_main TODOLIB)

add_executable(TodoListTest
        TodoListTests.cpp
)
target_link_libraries(TodoListTest PRIVATE GTest::gtest GTest::gtest_main TODOLIB)

# Aggiungi la directory di include per GTest
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# Aggiungi la directory di include per TODOLIB
include_directories(../../TODOLIST/include)

# Registrazione dei test
add_test(NAME DateTests COMMAND DateTest)
add_test(NAME ActivityTests COMMAND ActivityTest)
add_test(NAME TodoListTests COMMAND TodoListTest)
