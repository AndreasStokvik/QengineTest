#pragma once
#include <GLFW/glfw3.h>

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

