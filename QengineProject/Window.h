#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);    // Constructor
    ~Window();                                                  // Destructor

    void swapBuffers();                                         // Swap front and back buffers
    bool shouldClose();                                         // Check if window should close

    bool isKeyPressed(int key);

    // Set the mouse callback
    void setMouseCallback(GLFWcursorposfun callback) {
        glfwSetCursorPosCallback(window, callback);
    }
    void setUserPointer(void* pointer) {
        glfwSetWindowUserPointer(window, pointer);
    }

private:
    GLFWwindow* window;                                         // GLFW window handle
    void initGLFW();                                            // Initialize GLFW
};

#endif WINDOW_H