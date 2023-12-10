#include "InitializeOpenGL.h"

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>


void glhelpers::initalizeVertexBufferObject(GLuint &vbo, int num_of_triangles, float points[]){
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (9 * num_of_triangles) * sizeof(float), points, GL_STATIC_DRAW);
}
