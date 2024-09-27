#include "VertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    glGenBuffers(1, &id);  // Generate VBO
    glBindBuffer(GL_ARRAY_BUFFER, id);  // Bind the VBO
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);  // Upload data to GPU
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);  // Delete VBO when done
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);  // Bind the VBO
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);  // Unbind the VBO
}
