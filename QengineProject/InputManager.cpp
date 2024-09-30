#include "InputManager.h"
#include <GLFW/glfw3.h>

InputManager::InputManager() {
    keyStates.fill(false);  // Initialize all key states to false using std::array
}

void InputManager::processInput(Window& window, Camera& camera, float deltaTime) {
    // Movement keys (W, A, S, D, Space, Shift)
    if (isKeyPressed(window, GLFW_KEY_W))
        camera.processKeyboard(FORWARD, deltaTime);
    if (isKeyPressed(window, GLFW_KEY_S))
        camera.processKeyboard(BACKWARD, deltaTime);
    if (isKeyPressed(window, GLFW_KEY_A))
        camera.processKeyboard(LEFT, deltaTime);
    if (isKeyPressed(window, GLFW_KEY_D))
        camera.processKeyboard(RIGHT, deltaTime);
    if (isKeyPressed(window, GLFW_KEY_SPACE))
        camera.processKeyboard(UP, deltaTime);
    if (isKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
        camera.processKeyboard(DOWN, deltaTime);

    // Toggle cursor and camera movement with Escape key (once)
    if (isKeyPressedOnce(window, GLFW_KEY_ESCAPE)) {
        window.toggleCursor();
        camera.toggleMouseControl();
    }
}

// Check if a key was pressed just once
bool InputManager::isKeyPressedOnce(Window& window, int key) {
    if (glfwGetKey(window.getWindow(), key) == GLFW_PRESS) {
        if (!keyStates[key]) {
            keyStates[key] = true;  // Mark key as pressed
            return true;
        }
    }
    else if (glfwGetKey(window.getWindow(), key) == GLFW_RELEASE) {
        keyStates[key] = false;  // Reset state when key is released
    }
    return false;
}

// Standard key press check (for continuous actions)
bool InputManager::isKeyPressed(Window& window, int key) {
    return glfwGetKey(window.getWindow(), key) == GLFW_PRESS;
}
