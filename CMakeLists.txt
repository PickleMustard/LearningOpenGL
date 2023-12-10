cmake_minimum_required(VERSION 3.0.0)
project(opengl_exploration VERSION 0.1.0)

add_executable(opengl_exploration src/main.cpp)

target_link_libraries(opengl_exploration glfw)