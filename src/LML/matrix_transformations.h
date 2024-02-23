#pragma once
#include "matrix.h"
#include "vector.h"
#ifndef MATRIX_TRANSFORMATIONS_H
#define MATRIX_TRANSFORMATIONS_H

namespace LML {
    mat4x4 LookAtRH(const vector_3f& eye, const vector_3f& target, const vector_3f& up);
    mat4x4 Perspective(GLfloat fovrad, GLfloat screen_ratio, GLfloat near_plane, GLfloat far_plane);


}


#endif
