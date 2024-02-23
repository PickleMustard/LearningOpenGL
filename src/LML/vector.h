#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include <GL/glew.h>

namespace LML {
    struct vector_4f {
        GLfloat position[4];

        vector_4f() { position[0] = position[1] = position[2] = position[3] = 0;}

        vector_4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

        const GLfloat& operator[](int index) const {return position[index];}

        GLfloat& operator[](int index) {return position[index];}
    };

    struct vector_3f {
        GLfloat position[3];

        vector_3f() {position[0] = position[1] = position[2] = 0;}

         vector_3f(GLfloat x, GLfloat y, GLfloat z);

        const GLfloat& operator[](int index) const {return position[index];}

        GLfloat& operator[](int index) {return position[index];}

    };

    vector_3f operator-(const vector_3f& v1, const vector_3f& v2);
    vector_3f operator+(const vector_3f& v1, const vector_3f& v2);
    vector_4f operator*(const vector_4f& v, GLfloat s);
    vector_3f operator*(const vector_3f& v, GLfloat s);
    GLfloat magnitude(const vector_3f& v);
    vector_3f normalize(const vector_3f& v);
    vector_3f cross(const vector_3f& v1, const vector_3f& v2);
    GLfloat dot(const vector_3f& v1, const vector_3f& v2);
}

#endif
