#pragma once
#include <string>
#include <glad/glad.h>

class Texture {
public:
    Texture(const std::string& path);
    ~Texture();

    void bind(unsigned int unit = 0) const;             // Bind the texture to a specific texture unit
    unsigned int getID() const { return textureID; }    // Get the texture ID

private:
    unsigned int textureID;                     // OpenGL texture ID
    int width, height, nrChannels;              // Texture dimensions and color channels
    std::string filePath;                       // Path to the texture file

    void loadTexture(const std::string& path);  // Helper function to load the texture
};
