cmake_minimum_required(VERSION 3.28.0)
project(opengl_exploration VERSION 0.1.0)
#include(ExternalProject)
include(cmake/CPM.make)

#find_package(glfw3 3.4 REQUIRED)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

add_executable(opengl_exploration
              src/main.cpp
              src/InitHelp/InitializeOpenGL.cpp)

#ExternalProject_Add(glfw
#  GIT_REPOSITORY "https://github.com/glfw/glfw"
#  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
#  PREFIX ${CMAKE_CURRENT_BINARY_DIR}
#  INSTALL_COMAND ""
#  CMAKE_CACHE_ARGS "-DCMAKE_PREFIX_PATH:STRING=${GLFW_INSTALL_PREFIX}/lib/cmake"
#  DEPENDS glfw-external
#)

#ExternalProject_Get_Property(glfw install_dir)

add_dependencies(${PROJECT_NAME} glfw)
add_dependencies(${PROJECT_NAME} GLEW)

add_subdirectory(src/VectorMathAndObjects)
add_subdirectory(src/InitHelp)
add_subdirectory(src/GLObjects)
add_subdirectory(src/LML)
add_subdirectory(src/3DObjects)

target_include_directories(${PROJECT_NAME}
    PUBLIC src/InitHelp
    src/VectorMathAndObjects
    src/GLObjects
    src/LML
    src/3DObjects
)

target_link_directories(${PROJECT_NAME}
    PRIVATE src/InitHelp
    PRIVATE src/VectorMathAndObjects
    PRIVATE src/GLObjects
    PRIVATE src/LML
    PRIVATE src/3DObjects
)

target_link_libraries(${PROJECT_NAME} glfw GL GLEW InitHelp VectorMathAndObjects GLObjects LML 3DObjects)
