cmake_minimum_required(VERSION 3.0.0)
project(opengl_exploration VERSION 0.1.0)

add_executable(opengl_exploration src/main.cpp src/InitHelp/InitializeOpenGL.cpp)

add_subdirectory(src/VectorMathAndObjects)
add_subdirectory(src/InitHelp)
add_subdirectory(src/GLObjects)
add_subdirectory(src/LML)
add_subdirectory(src/3DObjects)


target_include_directories(${PROJECT_NAME}
    PUBLIC src/InitHelp
    PUBLIC src/VectorMathAndObjects
    PUBLIC src/GLObjects
    PUBLIC src/LML
    PUBLIC src/3DObjects
)

target_link_directories(${PROJECT_NAME}
    PRIVATE src/InitHelp
    PRIVATE src/VectorMathAndObjects
    PRIVATE src/GLObjects
    PRIVATE src/LML
    PRIVATE src/3DObjects
)

target_link_libraries(${PROJECT_NAME} glfw GL GLEW InitHelp VectorMathAndObjects GLObjects LML 3DObjects)
