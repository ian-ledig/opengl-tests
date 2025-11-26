#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D textureSampler;
uniform vec4 color;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform bool useTexture;

void main()
{
    vec4 sampled = useTexture ? texture(textureSampler, TexCoord) : vec4(1.0);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 lightDir = normalize(lightPos - FragPos);
    
    float diff = max(dot(Normal, lightDir), 0.0);
    
    vec3 diffuse = lightColor * diff;
    FragColor = sampled * color * vec4(ambient + diffuse, 1.0);
}