#include "Window.h"
#include <iostream>

// Constructor
Window::Window(int width, int height, const std::string& title) : width(width), height(height) {
    // Initialize GLFW
    initGLFW();

    // Create a GLFW window
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    cursorHidden = true;
    // Optionally set the cursor position to the center
    glfwSetCursorPos(window, width / 2, height / 2);
}

// Destructor
Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Window::getWindow()
{
    return window;
}

// Initialize GLFW
void Window::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        throw std::runtime_error("GLFW initialization failed.");
    }

    // Specify the version of OpenGL you want to use (for core profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Swap front and back buffers
void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

// Check if the window should close
bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

bool Window::isKeyPressed(int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

float Window::getAspectRatio() const {
    return static_cast<float>(width) / static_cast<float>(height);
}

void Window::toggleCursor() {
    if (cursorHidden) {
        // Show cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else {
        // Hide cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    // Flip the cursor state
    cursorHidden = !cursorHidden;
}
