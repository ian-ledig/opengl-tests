#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D textureSampler;
uniform vec4 color;
uniform bool useTexture;

void main()
{
    vec4 sampled = useTexture ? texture(textureSampler, TexCoord) : vec4(1.0);
    FragColor = sampled * color;
}