#version 330 core

out vec4 FragColor;

in vec3 Normal;  // Normal vector from vertex shader
in vec3 FragPos; // Fragment position from vertex shader
in vec2 TexCoords; // Texture coordinates from vertex shader

uniform sampler2D textureSampler; // Texture sampler
uniform vec3 lightPos; // Light position uniform
uniform vec3 lightColor; // Light color uniform
uniform vec3 viewPos; // Camera position uniform
uniform bool useTexture; // Boolean to check if a texture is used

void main() {
    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lighting = (ambient + diffuse + specular);

    if (useTexture) {
        FragColor = texture(textureSampler, TexCoords) * vec4(lighting, 1.0);
    } else {
        FragColor = vec4(lighting, 1.0);
    }
}
