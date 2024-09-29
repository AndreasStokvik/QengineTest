#include "Mesh.h"

// Constructor
Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices)
    : vertices(vertices), indices(indices) {
    setupMesh();
}

// Destructor to clean up resources
Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

// Setup the VAO, VBO, and EBO
void Mesh::setupMesh() {
    // Generate buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Load data into vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    // Load data into element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glBindVertexArray(0); // Unbind VAO
}

Mesh Mesh::createCube() {
    std::vector<glm::vec3> vertices = {
        // Cube vertices
        // Front face
        glm::vec3(-0.5f, -0.5f,  0.5f), // Bottom-left
        glm::vec3(0.5f, -0.5f,  0.5f), // Bottom-right
        glm::vec3(0.5f,  0.5f,  0.5f), // Top-right
        glm::vec3(-0.5f,  0.5f,  0.5f), // Top-left

        // Back face
        glm::vec3(-0.5f, -0.5f, -0.5f), // Bottom-left
        glm::vec3(0.5f, -0.5f, -0.5f), // Bottom-right
        glm::vec3(0.5f,  0.5f, -0.5f), // Top-right
        glm::vec3(-0.5f,  0.5f, -0.5f), // Top-left

        // Left face
        glm::vec3(-0.5f,  0.5f,  0.5f), // Top-right (front)
        glm::vec3(-0.5f,  0.5f, -0.5f), // Top-left (back)
        glm::vec3(-0.5f, -0.5f, -0.5f), // Bottom-left (back)
        glm::vec3(-0.5f, -0.5f,  0.5f), // Bottom-right (front)

        // Right face
        glm::vec3(0.5f,  0.5f,  0.5f),  // Top-left (front)
        glm::vec3(0.5f,  0.5f, -0.5f),  // Top-right (back)
        glm::vec3(0.5f, -0.5f, -0.5f),  // Bottom-right (back)
        glm::vec3(0.5f, -0.5f,  0.5f),  // Bottom-left (front)

        // Top face
        glm::vec3(-0.5f,  0.5f,  0.5f), // Top-left (front)
        glm::vec3(0.5f,  0.5f,  0.5f), // Top-right (front)
        glm::vec3(0.5f,  0.5f, -0.5f), // Top-right (back)
        glm::vec3(-0.5f,  0.5f, -0.5f), // Top-left (back)

        // Bottom face
        glm::vec3(-0.5f, -0.5f,  0.5f), // Bottom-left (front)
        glm::vec3(0.5f, -0.5f,  0.5f), // Bottom-right (front)
        glm::vec3(0.5f, -0.5f, -0.5f), // Bottom-right (back)
        glm::vec3(-0.5f, -0.5f, -0.5f)  // Bottom-left (back)
    };

    std::vector<unsigned int> indices = {
        // Cube indices
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        8, 9, 10,
        10, 11, 8,

        // Right face
        12, 13, 14,
        14, 15, 12,

        // Top face
        16, 17, 18,
        18, 19, 16,

        // Bottom face
        20, 21, 22,
        22, 23, 20
    };

    return Mesh(vertices, indices);
}

// Render the mesh (draw call)
void Mesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
