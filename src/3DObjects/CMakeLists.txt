add_library(3DObjects "")

target_sources(3DObjects
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/camera.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/camera.h
    )
target_include_directories(3DObjects
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
