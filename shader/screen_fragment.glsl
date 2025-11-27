#version 330 core

uniform sampler2D screenTexture;
uniform bool grayscale;

in vec2 uvCoords;

out vec4 FragColor;

void main() {
    if (grayscale) {
        vec3 col = texture(screenTexture, uvCoords).rgb;
        float avg = (col.r + col.g + col.b) / 3.0;
        FragColor = vec4(avg, avg, avg, 1.0);
    } else {
        FragColor = texture(screenTexture, uvCoords);
    }
}