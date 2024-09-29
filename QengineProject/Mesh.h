#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

class Mesh {
public:
    // Constructor
    Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices);

    // Destructor
    ~Mesh();

    static Mesh createCube();  // Static factory method

    // Render the mesh
    void draw();

private:
    GLuint VAO, VBO, EBO; // OpenGL object IDs

    void setupMesh();

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
};
