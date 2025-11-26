#version 330 core

struct Material {
    vec3 ambient;
    sampler2D diffuse;
}; 
  
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec4 color;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform bool useTexture;
uniform Material material;

void main()
{
    vec4 texture = useTexture ? texture(material.diffuse, TexCoord) : vec4(1.0);

    // ambient
    vec3 ambient = lightColor * material.ambient * texture.rgb;
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diff * texture.rgb;

    vec3 result = ambient + diffuse;
    FragColor = color * vec4(result, 1.0);
}