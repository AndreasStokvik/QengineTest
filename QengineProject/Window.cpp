#include "Window.h"
#include <iostream>

Window::Window(int width, int height, const std::string& title) : width(width), height(height) {
    initGLFW();

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create window.");
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);       // BG color
    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);                    // Dissable Culling
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Wireframe mode

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    cursorHidden = true;
    glfwSetCursorPos(window, width / 2, height / 2);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::setSize(int newWidth, int newHeight) {
    glfwSetWindowSize(window, newWidth, newHeight);
    width = newWidth;
    height = newHeight;
}

void Window::setResizeCallback(GLFWwindowsizefun callback) {
    glfwSetWindowSizeCallback(window, callback);
}

void Window::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        throw std::runtime_error("GLFW initialization failed.");
    }

    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::swapBuffers() {glfwSwapBuffers(window);}
bool Window::shouldClose() {return glfwWindowShouldClose(window);}
bool Window::isKeyPressed(int key) {return glfwGetKey(window, key) == GLFW_PRESS;}
float Window::getAspectRatio() const {return static_cast<float>(width) / static_cast<float>(height);}

void Window::toggleCursor() {
    if (cursorHidden) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);      // Show cursor
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // Hide cursor
    }
    cursorHidden = !cursorHidden;
}
