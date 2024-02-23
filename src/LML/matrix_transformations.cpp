#include "matrix.h"
#include "matrix_transformations.h"
#include "vector.h"
#include <cmath>
LML::mat4x4 LML::LookAtRH(const vector_3f &eye, const vector_3f &target, const vector_3f &up){
    vector_3f zaxis = normalize(eye - target);
    vector_3f xaxis = normalize(cross(up, zaxis));
    vector_3f yaxis = cross(zaxis, xaxis);

    mat4x4 orientation = mat4x4(
            vector_4f( xaxis[0], yaxis[0], zaxis[0], 0.0f),
            vector_4f( xaxis[1], yaxis[1], zaxis[1], 0.0f),
            vector_4f( xaxis[2], yaxis[2], zaxis[2], 0.0f),
            vector_4f( 0.0f, 0.0f, 0.0f, 1.0f)
            );
    mat4x4 translate = mat4x4(
            vector_4f(1.0f, 0.0f, 0.0f, 0.0f),
            vector_4f(0.0f, 1.0f, 0.0f, 0.0f),
            vector_4f(0.0f, 0.0f, 1.0f, 0.0f),
            vector_4f(-eye[0], -eye[1], -eye[2], 1.0f)
            );

    return ( orientation * translate);
}

LML::mat4x4 LML::Perspective(GLfloat fovrad, GLfloat screen_ratio, GLfloat near_plane, GLfloat far_plane) {
    GLfloat tanHalfFOVy = tanf(fovrad / 2.0f);

    mat4x4 result = mat4x4();

    result[0][0] = 1.0f / (screen_ratio * tanHalfFOVy);
    result[1][1] = 1.0f / (tanHalfFOVy);
    result[2][2] = -(near_plane + far_plane) / (far_plane - near_plane);
    result[2][3] = -1.0f;
    result[3][2] = -(2.0f * far_plane * near_plane) / (far_plane - near_plane);
    result[3][3] = 0.0f;

    return result;
}
