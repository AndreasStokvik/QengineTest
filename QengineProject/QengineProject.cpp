#include "Window.h"
#include "Shader.h"

int main() {
    Window window(800, 600, "My OpenGL Window");

    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    // Main loop
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        window.swapBuffers();

        glfwPollEvents();
    }

    return 0;
}