#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <array>
#include "Window.h"
#include "Camera.h"

class InputManager {
public:
    InputManager();

    void processInput(Window& window, Camera& camera, float deltaTime);
    bool isKeyPressedOnce(Window& window, int key);
    bool isKeyPressed(Window& window, int key);

private:
    std::array<bool, 1024> keyStates;  // Replace with std::array for easier management
};

#endif // INPUTMANAGER_H
