#include "InitializeOpenGL.h"

#include <GL/glew.h>
#include <sstream>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

void glhelpers::initalizeVertexBufferObject(GLuint& vbo, int num_of_triangles, const float points[]){
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (9 * num_of_triangles) * sizeof(float), points, GL_STATIC_DRAW);
}


void glhelpers::initializeVertexArrayObject(GLuint& vao, GLuint &vbo) {
    //Generate VAO
    glGenVertexArrays(1, &vao);
    //Bind it
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //0 define the layout for attribute # 0.
    //3 manes the variables are vec3 of type GL_FLOAT
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 , 0);
}

void glhelpers::initializeNormalArrayObject(GLuint& snao, GLuint &snbo) {
    //Generate VAO
    glGenVertexArrays(1, &snao);
    //Bind it
    glBindVertexArray(snao);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, snbo);
    //0 define the layout for attribute # 0.
    //3 manes the variables are vec3 of type GL_FLOAT
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0 , 0);
}
std::string glhelpers::parseShaderFile(const char* filename){
    std::string parsed_shader_information;
    std::ifstream fd(filename, std::ifstream::in);
    std::stringstream shader_stream;
    shader_stream << fd.rdbuf();
    fd.close();
    parsed_shader_information = shader_stream.str();

    printf("Final Shader file: %s\n", parsed_shader_information.c_str());
    return parsed_shader_information;
}

