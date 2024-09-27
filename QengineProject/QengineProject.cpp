#include "Window.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

int main() {
    Window window(800, 600, "OpenGL Window");

    // Define vertex data (for a triangle)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Create and bind the VAO and VBO
    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));

    // Define the layout of the vertex data (for position data)
    vao.bind();
    glEnableVertexAttribArray(0);  // Enable vertex attribute 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    // Main loop
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind();
        shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.swapBuffers();

        glfwPollEvents();
    }

    return 0;
}