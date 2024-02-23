#include "vector.h"
#include <GL/gl.h>
#include <cmath>

namespace LML {
    LML::vector_4f::vector_4f(float x, float y, float z, float w) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
        position[3] = w;
    }

    LML::vector_3f::vector_3f(GLfloat x, GLfloat y, GLfloat z) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
    }

    LML::vector_3f operator*(const LML::vector_3f& v, GLfloat s) {
        return vector_3f(v[0] * s, v[1] * s, v[2] * s);
    }

    LML::vector_3f operator-(const vector_3f &v1, const vector_3f &v2){
        return vector_3f(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
    }

    LML::vector_3f operator+(const vector_3f& v1, const vector_3f& v2) {
        return vector_3f(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
    }

    GLfloat magnitude(const vector_3f &v) {
        return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    LML::vector_3f normalize(const vector_3f &v) {
        GLfloat mag = magnitude(v);
        if(mag > 0) {
            return vector_3f(v[0] / mag, v[1] / mag, v[2] / mag);
        }
        return vector_3f();
    }

    LML::vector_3f cross(const vector_3f &v1, const vector_3f &v2) {
        return vector_3f(v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0]);
    }

    GLfloat dot(const vector_3f &v1, const vector_3f &v2) {
        return v1[0]*v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    }
}
