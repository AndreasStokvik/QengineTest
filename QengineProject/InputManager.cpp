// InputManager.cpp
#include "InputManager.h"
#include <GLFW/glfw3.h>

void InputManager::processInput(Window& window, Camera& camera, float deltaTime) {
    // Handle camera movement with WASD keys
    if (window.isKeyPressed(GLFW_KEY_W)) {
        camera.processKeyboard(FORWARD, deltaTime);
    }
    if (window.isKeyPressed(GLFW_KEY_S)) {
        camera.processKeyboard(BACKWARD, deltaTime);
    }
    if (window.isKeyPressed(GLFW_KEY_A)) {
        camera.processKeyboard(LEFT, deltaTime);
    }
    if (window.isKeyPressed(GLFW_KEY_D)) {
        camera.processKeyboard(RIGHT, deltaTime);
    }

    // Handle vertical movement (space and shift keys)
    if (window.isKeyPressed(GLFW_KEY_SPACE)) {
        camera.processKeyboard(UP, deltaTime);
    }
    if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        camera.processKeyboard(DOWN, deltaTime);
    }
}
