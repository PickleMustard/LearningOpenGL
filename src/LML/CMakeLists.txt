add_library(LML SHARED "")

target_sources(LML
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/matrix.cpp
        ${CMAKE_CURRENT_LIST_DIR}/vector.cpp
        ${CMAKE_CURRENT_LIST_DIR}/matrix_transformations.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/matrix.h
        ${CMAKE_CURRENT_LIST_DIR}/vector.h
        ${CMAKE_CURRENT_LIST_DIR}/matrix_transformations.h
    )
target_include_directories(LML
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
