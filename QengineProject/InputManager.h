// InputManager.h
#pragma once
#include "Window.h"
#include "Camera.h"

class InputManager {
public:
    static void processInput(Window& window, Camera& camera, float deltaTime);
};
