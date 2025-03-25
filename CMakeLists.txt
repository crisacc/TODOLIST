cmake_minimum_required(VERSION 3.20)
project(TODOLIST)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(tests)

# Aggiungi la sottocartella che contiene il codice sorgente della libreria
add_subdirectory(TODOLIST)

# Aggiungi l'eseguibile main
add_executable(TODOLIST_main main.cpp)

# Collega l'eseguibile alla libreria TODOLIST_LIB
target_link_libraries(TODOLIST_main PRIVATE TODOLIST_LIB)
