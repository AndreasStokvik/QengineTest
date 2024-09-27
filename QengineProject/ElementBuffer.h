#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H

class ElementBuffer {
public:
    ElementBuffer(const unsigned int* indices, unsigned int count);
    ~ElementBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getCount() const { return count; }

private:
    unsigned int id;      // Stores the EBO ID
    unsigned int count;   // Number of elements (indices) to draw
};

#endif // ELEMENT_BUFFER_H
