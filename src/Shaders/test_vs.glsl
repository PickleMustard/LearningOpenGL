#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 color;

uniform mat4 camMatrix;

void main() {
    gl_Position = camMatrix * vec4(aPos, 1.0);
    color = aCol;
}
