#include "VertexArray.h"
#include <glad/glad.h>  // Make sure GLAD is included for OpenGL functions

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);  // Generate VAO
    glBindVertexArray(id);      // Bind VAO
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);  // Delete VAO when done
}

void VertexArray::bind() const {
    glBindVertexArray(id);  // Bind the VAO
}

void VertexArray::unbind() const {
    glBindVertexArray(0);   // Unbind the VAO
}
