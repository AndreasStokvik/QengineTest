#ifndef CAMERA_H
#define CAMERA_H

#include "Window.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Shader; // Forward declaration

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

    glm::mat4 projection;

    float fov;           // Field of view
    float nearPlane;     // Near clipping plane
    float farPlane;      // Far clipping plane


    // Euler angles
    float yaw;
    float pitch;

    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, const std::shared_ptr<Window>& window);

    // Get the view matrix (camera transformation)
    glm::mat4 getViewMatrix();

    // Processes input from keyboard movement
    void processKeyboard(CameraMovement direction, float deltaTime);

    // Processes input from mouse movement
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    void setProjectionUniform(const std::shared_ptr<Shader> shader);

    void updateProjectionMatrix(const std::shared_ptr<Window>& window);

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
