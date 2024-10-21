#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    GLFWwindow* getWindow() { return window; };
    void swapBuffers();
    bool shouldClose();
    bool isKeyPressed(int key);
    float getAspectRatio() const;
    void toggleCursor();

    // Set the mouse callback
    void setMouseCallback(GLFWcursorposfun callback) {
        glfwSetCursorPosCallback(window, callback);
    }
    void setUserPointer(void* pointer) {
        glfwSetWindowUserPointer(window, pointer);
    }

    void setSize(int newWidth, int newHeight);
    void setResizeCallback(GLFWwindowsizefun callback);

private:
    GLFWwindow* window;
    int width, height;
    bool cursorHidden;

    void initGLFW();
};

#endif WINDOW_H