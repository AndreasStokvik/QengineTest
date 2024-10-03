#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"

// Vertex structure
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

// Texture data structure
struct TextureData {
    unsigned int id;
    std::string type;
    std::string path;
};

class Model {
public:
    // Constructor
    Model(const std::string& path);

    // Load model function
    void loadModel(const std::string& path);

    // Draw function
    void draw(Shader& shader);

private:
    // Process node
    void processNode(aiNode* node, const aiScene* scene);

    // Process a single mesh
    void processMesh(aiMesh* mesh, const aiScene* scene);

    // Member variables
    std::vector<Vertex> vertices;           // Stores vertices
    std::vector<unsigned int> indices;      // Stores indices
    std::string directory;                   // Model directory
};

#endif // MODEL_H
