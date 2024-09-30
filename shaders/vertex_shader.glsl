#version 330 core

layout (location = 0) in vec3 aPos;  // Position of the vertex
layout (location = 1) in vec2 aTexCoord;  // Texture coordinate

out vec2 TexCoord;  // Pass to fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;  // Pass texture coordinate to fragment shader
}
