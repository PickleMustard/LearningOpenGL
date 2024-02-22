add_library(GLObjects "")

target_sources(GLObjects
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/EBO.cpp
        ${CMAKE_CURRENT_LIST_DIR}/VAO.cpp
        ${CMAKE_CURRENT_LIST_DIR}/VBO.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/EBO.h
        ${CMAKE_CURRENT_LIST_DIR}/VAO.h
        ${CMAKE_CURRENT_LIST_DIR}/VBO.h
    )
target_include_directories(GLObjects
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
