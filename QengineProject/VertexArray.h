#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

private:
    unsigned int id;  // Stores the ID of the VAO
};

#endif // VERTEX_ARRAY_H
