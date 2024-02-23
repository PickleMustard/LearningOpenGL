#include "camera.h"
#include "../LML/matrix_transformations.h"
#include "../LML/matrix.h"

camera::camera()
    : camera_location(0.0f, 0.0f, 2.0f)
    , screen_width(800)
    , screen_height(800)
    , orientation(0.0f, 0.0f, -1.0f)
{}

camera::camera(const LML::vector_3f& location, int width, int height)
    : camera_location(location)
    , screen_width(width)
    , screen_height(height)
    , orientation(0.0f, 0.0f, -1.0f)
{}


void camera::constructViewTransformationMatrix(GLfloat fovdeg, float nearPlane, float farPlane, GLuint shaderID, const char* uniform) {
    LML::mat4x4 view;
    LML::mat4x4 projection;
    LML::mat4x4 result;

    view = LML::LookAtRH(camera_location, camera_location + orientation, up);
    projection = LML::Perspective((fovdeg * 0.01745329251994329576923690768489f),(float)screen_width/screen_height, nearPlane, farPlane);
    result = (projection * view);


    glUniformMatrix4fv(glGetUniformLocation(shaderID, uniform), 1, GL_FALSE, &(result)[0][0]);
}

