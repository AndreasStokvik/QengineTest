#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <array>
#include <memory>
#include "Window.h"
#include "Camera.h"

class Timer {
public:
    float getDeltaTime() {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        return deltaTime;
    }
private:
    float lastFrame = 0.0f;
};

class InputManager {
public:
    InputManager(const std::shared_ptr<Window>& window, const std::shared_ptr<Camera>& camera);

    void processInput(const std::shared_ptr<Window>& window, const std::shared_ptr<Camera>& camera);
    bool isKeyPressedOnce(const std::shared_ptr<Window>& window, int key);
    bool isKeyPressed(const std::shared_ptr<Window>& window, int key);
    void toggleMouseControl();
    void handleMouseMovement(double xpos, double ypos, const std::shared_ptr<Camera>& camera);
    void setMouseCallback(const std::shared_ptr<Window>& window, const std::shared_ptr<Camera>& camera);

private:
    std::array<bool, 1024> keyStates;
    float lastX, lastY;
    bool firstMouse;
    bool mouseControl;
};

#endif // INPUTMANAGER_H
