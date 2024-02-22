#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GL/glew.h>

class VBO {
    public:
        //The OpenGL ID of the Vertex Buffer Object
        GLuint ID;

        //Constructor to generate the Vertex Buffer Object
        //Fills the newly generated buffer with vertices
        VBO(GLfloat* vertices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};

#endif
