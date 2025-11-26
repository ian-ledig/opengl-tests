#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
}; 
  
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D textureSampler;
uniform vec4 color;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform bool useTexture;
uniform Material material;

void main()
{
    vec4 sampled = useTexture ? texture(textureSampler, TexCoord) : vec4(1.0);

    // ambient
    vec3 ambient = lightColor * material.ambient;
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diff * material.diffuse;

    vec3 result = ambient + diffuse;
    FragColor = sampled * color * vec4(result, 1.0);
}