#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void swapBuffers();
    bool shouldClose();
    bool isKeyPressed(int key);

    // Set the mouse callback
    void setMouseCallback(GLFWcursorposfun callback) {
        glfwSetCursorPosCallback(window, callback);
    }
    void setUserPointer(void* pointer) {
        glfwSetWindowUserPointer(window, pointer);
    }

    GLFWwindow* getWindow();

    float getAspectRatio() const;

    void toggleCursor();
private:
    GLFWwindow* window;
    void initGLFW();

    int width;
    int height;

    bool cursorHidden;
};

#endif WINDOW_H