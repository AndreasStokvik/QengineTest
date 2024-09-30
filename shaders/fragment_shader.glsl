#version 330 core

in vec2 TexCoord;  // Texture coordinates from the vertex shader
out vec4 FragColor;

uniform sampler2D textureSampler;  // The texture sampler

void main() {
    FragColor = texture(textureSampler, TexCoord);  // Sample the texture at the given coordinates
}
