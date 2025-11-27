#version 330 core
layout (location = 0) in vec2 vpos;
layout (location = 1) in vec2 vcoords;

out vec2 uvCoords;

void main() {
    uvCoords = vcoords;
    gl_Position = vec4(vpos, 0.0, 1.0);
}