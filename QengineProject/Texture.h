#pragma once
#include <string>
#include <glad/glad.h>

class Texture {
public:
    // Constructor to load a texture from a file
    Texture(const std::string& path);

    // Destructor
    ~Texture();

    // Bind the texture to a specific texture unit
    void bind(unsigned int unit = 0) const;

    // Get the texture ID
    unsigned int getID() const { return textureID; }

private:
    unsigned int textureID;  // OpenGL texture ID
    int width, height, nrChannels;  // Texture dimensions and color channels
    std::string filePath;  // Path to the texture file

    void loadTexture(const std::string& path);  // Helper function to load the texture
};
