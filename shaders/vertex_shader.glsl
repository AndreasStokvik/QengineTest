#version 330 core

layout(location = 0) in vec3 aPos;      // Vertex position
layout(location = 1) in vec3 aNormal;   // Normal attribute
layout(location = 2) in vec2 aTexCoord;  // Texture coordinate attribute

out vec3 FragPos;    // Position passed to fragment shader
out vec3 Normal;     // Normal passed to fragment shader
out vec2 TexCoords;  // Texture coordinates passed to fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal; // Correct normal transformation
    TexCoords = aTexCoord;  // Pass the texture coordinates to the fragment shader
    gl_Position = projection * view * vec4(FragPos, 1.0);
}