#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>  // Required for glm::value_ptr
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor: Load, compile, and link shaders
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    // Load shader source code
    std::string vertexCode = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);

    // Compile vertex and fragment shaders
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // Create the shader program and link the shaders
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Clean up by deleting the shaders (they are linked now, so not needed)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Destructor: Clean up by deleting the shader program
Shader::~Shader() {
    glDeleteProgram(programID);
}

// Activate the shader program
void Shader::use() const {
    glUseProgram(programID);
}

// Set a float uniform in the shader
void Shader::setUniform(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

// Set an integer uniform in the shader (for texture samplers)
void Shader::setUniform(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

// Set a matrix uniform (like for transformation matrices)
void Shader::setUniform(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniform(const std::string& name, const glm::vec3& vector) {
    int location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: uniform '" << name << "' not found or not used in the shader program!" << std::endl;
    }
    glUniform3fv(location, 1, glm::value_ptr(vector));
}

// Set an integer uniform in the shader (for texture samplers)
void Shader::setInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

// Load the shader source code from a file
std::string Shader::loadShaderSource(const std::string& path) {
    std::ifstream shaderFile;
    shaderFile.open(path);

    if (!shaderFile.is_open()) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << path << std::endl;
        throw std::runtime_error("Shader file couldn't be read.");
    }

    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    shaderFile.close();

    return buffer.str();
}

// Compile a shader (vertex or fragment)
unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}
