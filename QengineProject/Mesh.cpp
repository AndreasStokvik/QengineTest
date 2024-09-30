#include "Mesh.h"

// Constructor
Mesh::Mesh(const std::vector<float> vertices, const std::vector<unsigned int>& indices)
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    // Load data into element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // 3 floats for position

    // Texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // 2 floats for texture coords

    glBindVertexArray(0); // Unbind VAO
}

Mesh Mesh::createCube() {
    std::vector<float> vertices = {
        // positions          // texture coords
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-left

        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left

        // Left face
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-right (front)
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, // Top-left (back)
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-left (back)
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // Bottom-right (front)

        // Right face
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-left (front)
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, // Top-right (back)
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right (back)
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // Bottom-left (front)

         // Top face
         -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-left (front)
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right (front)
          0.5f,  0.5f, -0.5f,  1.0f, 0.0f, // Top-right (back)
         -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, // Top-left (back)

         // Bottom face
         -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // Bottom-left (front)
          0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // Bottom-right (front)
          0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right (back)
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f  // Bottom-left (back)
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
