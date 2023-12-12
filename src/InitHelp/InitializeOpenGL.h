#pragma once

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <string>

namespace glhelpers{
    void initalizeVertexBufferObject(GLuint& vbo, int num_of_triangles, float points[]);
    void initializeVertexArrayObject(GLuint& vao, GLuint &vbo);
    std::string parseShaderFile(const char* filename);

}
