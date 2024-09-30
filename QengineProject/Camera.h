#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    // Camera attributes
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

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

    // Get the view matrix (camera transformation)
    glm::mat4 getViewMatrix();

    // Processes input from keyboard movement
    void processKeyboard(CameraMovement direction, float deltaTime);

    // Processes input from mouse movement
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // Processes input from the mouse scroll wheel (for zooming)
    void processMouseScroll(float yoffset);

    // Handle mouse movement input
    void handleMouseMovement(float xpos, float ypos);

    void toggleMouseControl();
private:
    // Recalculate the camera's vectors (direction)
    void updateCameraVectors();

    // Add mouse-specific members for handling the first frame and mouse position
    float lastX = 800.0f / 2.0f;
    float lastY = 600.0f / 2.0f;
    bool firstMouse = true;
    bool mouseControl;
};

#endif // CAMERA_H
