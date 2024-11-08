add_executable(basic_tests
            test_file.cpp
)

target_link_libraries(basic_tests PRIVATE ${GTEST_LIBRARIES} TODOLIB)


target_include_directories(basic_tests PRIVATE ../lib/googletest-1.15.2/googletest/include)


add_test(NAME basic_tests COMMAND basic_tests)