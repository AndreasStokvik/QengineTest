#include "Window.h"
//#include "Shader.h"

int main() {
    Window window(800, 600, "My OpenGL Window");

    // Create the shader program
    // Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    // Main loop
    while (!window.shouldClose()) {
        // Rendering logic
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader program
        //shader.use();

        // Swap buffers
        window.swapBuffers();

        // Poll for events
        glfwPollEvents();
    }

    return 0;
}