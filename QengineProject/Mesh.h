#pragma once
#include <iostream>
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

struct Vertex {
    glm::vec3 Position;     // Vertex position
    glm::vec3 Normal;       // Vertex normal
    glm::vec2 TexCoords;    // Texture coordinates
};

// Rename Texture struct to TextureData
struct TextureData { // Change the name here
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // Constructor
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<TextureData>& textures); // Change type here

    // Destructor
    ~Mesh();

    // Static factory method
    static Mesh createCube();

    // Render the mesh
    void draw(Shader& shader);

private:
    GLuint VAO, VBO, EBO; // OpenGL object IDs

    void setupMesh();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureData> textures; // Change type here
};
