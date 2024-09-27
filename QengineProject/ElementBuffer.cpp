#include "ElementBuffer.h"
#include <glad/glad.h>

ElementBuffer::ElementBuffer(const unsigned int* indices, unsigned int count)
    : count(count) {
    glGenBuffers(1, &id);  // Generate the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);  // Bind the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);  // Upload index data
}

ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &id);  // Delete the EBO when done
}

void ElementBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);  // Bind the EBO
}

void ElementBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   // Unbind the EBO
}
