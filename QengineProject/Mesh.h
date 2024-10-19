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

struct TextureData {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<TextureData>& textures);

    ~Mesh();

    // Static factory method
    static Mesh createCube();

    void draw(Shader& shader);

private:
    GLuint VAO, VBO, EBO;

    void setupMesh();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureData> textures;
};
