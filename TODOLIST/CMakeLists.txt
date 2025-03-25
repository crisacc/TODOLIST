# Imposta i file sorgente per la libreria
set(SOURCES
        Activity.cpp
        Date.cpp
        TodoList.cpp
)

# Crea la libreria (può essere statica o condivisa)
add_library(TODOLIST_LIB ${SOURCES})

# Specifica la directory degli header (incluso json.hpp)
target_include_directories(TODOLIST_LIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
