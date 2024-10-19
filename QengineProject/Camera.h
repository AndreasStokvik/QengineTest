#ifndef CAMERA_H
#define CAMERA_H

#include "Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler angles
    float yaw;
    float pitch;

    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

    // Get the view matrix (camera transformation)
    glm::mat4 getViewMatrix();

    // Processes input from keyboard movement
    void processKeyboard(CameraMovement direction, float deltaTime);

    // Processes input from mouse movement
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // Processes input from the mouse scroll wheel (not used)
    void processMouseScroll(float yoffset);

    glm::vec3 getPosition() const;
private:
    void updateCameraVectors();

    float lastX = 800.0f / 2.0f;
    float lastY = 600.0f / 2.0f;
    bool firstMouse = true;
};

#endif // CAMERA_H
