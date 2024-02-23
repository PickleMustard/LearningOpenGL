#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <GL/glew.h>

#include "vector.h"
namespace LML {
    struct mat4x4 {
        vector_4f columns[4];

        //Create a matrix of 4 columns by 4 rows
        mat4x4();
        mat4x4(vector_4f a, vector_4f b, vector_4f c, vector_4f d);

        //As the matrix is in column-major format, we will access it column -> rows
        const vector_4f& operator[](int index) const {return columns[index];}

        vector_4f& operator[](int index) {return columns[index];}

    };

    vector_4f operator*(const mat4x4& M,const vector_4f& V);
    mat4x4 operator*(const mat4x4& M, const mat4x4& M2);
}
#endif
