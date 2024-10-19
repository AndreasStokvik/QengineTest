#include "InputManager.h"
#include <GLFW/glfw3.h>

struct InputCameraContext {
    InputManager* inputManager;
    std::shared_ptr<Camera> camera;
};

std::unique_ptr<Timer> timer = std::make_unique<Timer>();

InputManager::InputManager(const std::shared_ptr<Window>& window, const std::shared_ptr<Camera>& camera)
    : lastX(400), lastY(300), firstMouse(true) {
    keyStates.fill(false);
    setMouseCallback(window, camera);
}

void InputManager::processInput(const std::shared_ptr <Window>& window, const std::shared_ptr<Camera>& camera) {
    float deltaTime = timer->getDeltaTime();
    // Movement keys (W, A, S, D, Space, Shift)
    if (isKeyPressed(window, GLFW_KEY_W))
        camera->processKeyboard(FORWARD, deltaTime);
    if (isKeyPressed(window, GLFW_KEY_S))
        camera->processKeyboard(BACKWARD, deltaTime);
    if (isKeyPressed(window, GLFW_KEY_A))
        camera->processKeyboard(LEFT, deltaTime);
    if (isKeyPressed(window, GLFW_KEY_D))
        camera->processKeyboard(RIGHT, deltaTime);
    if (isKeyPressed(window, GLFW_KEY_SPACE))
        camera->processKeyboard(UP, deltaTime);
    if (isKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
        camera->processKeyboard(DOWN, deltaTime);

    // Toggle cursor and camera movement with Escape key (once)
    if (isKeyPressedOnce(window, GLFW_KEY_ESCAPE)) {
        window->toggleCursor();
        toggleMouseControl();
    }
}

// Check if a key was pressed just once
bool InputManager::isKeyPressedOnce(const std::shared_ptr <Window>& window, int key) {
    if (glfwGetKey(window->getWindow(), key) == GLFW_PRESS) {
        if (!keyStates[key]) {
            keyStates[key] = true;  // Mark key as pressed
            return true;
        }
    }
    else if (glfwGetKey(window->getWindow(), key) == GLFW_RELEASE) {
        keyStates[key] = false;  // Reset state when key is released
    }
    return false;
}

// Standard key press check (for continuous actions)
bool InputManager::isKeyPressed(const std::shared_ptr <Window>& window, int key) {
    return glfwGetKey(window->getWindow(), key) == GLFW_PRESS;
}

void InputManager::toggleMouseControl()
{
    mouseControl = !mouseControl;
}

void InputManager::handleMouseMovement(double xpos, double ypos, const std::shared_ptr<Camera>& camera) {
    if (firstMouse) {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - lastX;
    float yoffset = lastY - static_cast<float>(ypos);

    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    if (mouseControl) {
        camera->processMouseMovement(xoffset, yoffset);
    }
}

void InputManager::setMouseCallback(const std::shared_ptr<Window>& window, const std::shared_ptr<Camera>& camera) {
    // Create a struct that holds both InputManager and Camera pointers
    auto* context = new InputCameraContext{ this, camera };
    glfwSetWindowUserPointer(window->getWindow(), context);

    // Use a static callback that retrieves the InputManager and Camera from the user pointer
    glfwSetCursorPosCallback(window->getWindow(), [](GLFWwindow* glfwWindow, double xpos, double ypos) {
        auto* context = static_cast<InputCameraContext*>(glfwGetWindowUserPointer(glfwWindow));
        context->inputManager->handleMouseMovement(xpos, ypos, context->camera);
        });
}

