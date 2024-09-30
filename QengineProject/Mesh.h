#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;     // Vertex position
    glm::vec3 Normal;       // Vertex normal
    glm::vec2 TexCoords;    // Texture coords
};

class Mesh {
public:
    // Constructor
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    // Destructor
    ~Mesh();

    static Mesh createCube();  // Static factory method

    // Render the mesh
    void draw();

private:
    GLuint VAO, VBO, EBO; // OpenGL object IDs

    void setupMesh();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

};
