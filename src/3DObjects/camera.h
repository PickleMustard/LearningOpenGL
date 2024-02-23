#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "../LML/matrix.h"
#include "../LML/vector.h"
#include <GL/gl.h>


class camera {
    private:
        LML::vector_3f camera_location, looking_at_location, orientation;
        LML::vector_3f up = LML::vector_3f(0.0f, 1.0f, 0.0f);
        GLfloat fov;
        //LML::mat4x4 temp;
        int screen_width, screen_height;

    public:
        camera();

        camera(const LML::vector_3f& cl, int width, int height);

        void constructViewTransformationMatrix(GLfloat fovdeg, float nearPlane, float farPlane, GLuint shaderID, const char* uniform);
};


#endif

