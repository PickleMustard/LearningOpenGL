#pragma once

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

namespace glhelpers{
    void initalizeVertexBufferObject(GLuint &vbo, int num_of_triangles, float points[]);


}
