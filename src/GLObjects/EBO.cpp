#include "EBO.h"


//Create the buffer in the current context
//Creates a single buffer and binds it
//Included data is contained in indicies
EBO::EBO(GLuint* indices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(GLuint), indices, GL_STATIC_DRAW);
}


//Bind the buffer object to the current OpenGL context
void EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

//Unbind the buffer from the current OpenGL context
void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Delete the buffer
void EBO::Delete() {
    glDeleteBuffers(1, &ID);
}
