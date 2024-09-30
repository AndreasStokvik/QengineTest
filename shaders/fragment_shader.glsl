#version 330 core

out vec4 FragColor;

in vec3 Normal;  // Normal vector from vertex shader
in vec3 FragPos; // Fragment position from vertex shader
in vec2 TexCoords; // Texture coordinates from vertex shader

uniform sampler2D textureSampler; // Texture sampler
uniform vec3 lightPos; // Light position uniform
uniform vec3 lightColor; // Light color uniform
uniform vec3 viewPos; // Camera position uniform

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

    // Combine results
    vec3 textureColor = texture(textureSampler, TexCoords).rgb; // Sample the texture
    vec3 result = (ambient + diffuse + specular) * textureColor; // Combine texture with lighting
    FragColor = vec4(result, 1.0); // Output final color
}
