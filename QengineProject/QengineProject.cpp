#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include "InputManager.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));  // Start the camera 3 units away from the origin
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    camera->handleMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
}

int main() {
    Window window(800, 600, "OpenGL Window");
    window.setUserPointer(&camera);
    window.setMouseCallback(mouse_callback);

    Mesh cube = Mesh::createCube();
    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    shader.use();

    Transform transform(camera, window);

    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        InputManager::processInput(window, camera, deltaTime);
        transform.update(camera, window);

        shader.setUniform("model", transform.model);
        shader.setUniform("view", transform.view);
        shader.setUniform("projection", transform.projection);

        shader.use();
        cube.draw();

        window.swapBuffers();
    }

    return 0;
}