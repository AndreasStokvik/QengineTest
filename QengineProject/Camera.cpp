#define GLM_ENABLE_EXPERIMENTAL
#include "Camera.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// Constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

// Returns the view matrix calculated using the camera's position and orientation
glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

// Processes input received from a keyboard and moves the camera accordingly
void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD) {
        position += front * velocity;
        //std::cout << "Moving Forward: " << glm::to_string(position) << std::endl; // Debug output
    }
    if (direction == BACKWARD) {
        position -= front * velocity;
        //std::cout << "Moving Backward: " << glm::to_string(position) << std::endl; // Debug output
    }
    if (direction == LEFT) {
        position -= right * velocity;
        //std::cout << "Strafing Left: " << glm::to_string(position) << std::endl; // Debug output
    }
    if (direction == RIGHT) {
        position += right * velocity;
        //std::cout << "Strafing Right: " << glm::to_string(position) << std::endl; // Debug output
    }
    if (direction == UP) {
        position += worldUp * velocity;
        //std::cout << "Strafing Right: " << glm::to_string(position) << std::endl; // Debug output
    }
    if (direction == DOWN) {
        position -= worldUp * velocity;
        //std::cout << "Strafing Right: " << glm::to_string(position) << std::endl; // Debug output
    }
}

// Processes input received from a mouse, adjusting the yaw and pitch
void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Constrain the pitch to avoid flipping at high/low angles
    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // Update front, right, and up vectors using the updated Euler angles
    updateCameraVectors();
}

// Processes input received from the scroll wheel for zooming
void Camera::processMouseScroll(float yoffset) {
    zoom -= yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::vec3 Camera::getPosition() const {
    return position;
}