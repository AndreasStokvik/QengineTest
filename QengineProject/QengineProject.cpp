#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <chrono>
#include <cstdlib>

#include "Window.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Camera.h"

void processInput(Window& window, Camera& camera, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

float deltaTime = 0.0f;  // Time between current frame and last frame
float lastFrame = 0.0f;  // Time of the last frame

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));  // Start the camera 3 units away from the origin

int main() {

    Window window(800, 600, "OpenGL Window");
    window.setUserPointer(&camera);
    window.setMouseCallback(mouse_callback);


    // Define 3D vertices for a cube
    float vertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        // Back face
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    // Define the element indices for the cube (for indexed drawing)
    unsigned int indices[] = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        0, 4, 7,
        7, 3, 0,

        // Right face
        1, 5, 6,
        6, 2, 1,

        // Top face
        3, 7, 6,
        6, 2, 3,

        // Bottom face
        0, 4, 5,
        5, 1, 0,
    };

    // Create and bind the VAO, VBO, and EBO
    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));
    ElementBuffer ebo(indices, sizeof(indices) / sizeof(unsigned int));

    // Define the layout of the vertex data (for position data)
    vao.bind();
    glEnableVertexAttribArray(0);  // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    shader.use();


    // Set up the 3D transformation matrices
    glm::mat4 model = glm::mat4(1.0f);  // Model matrix
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));  // View matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);  // Projection matrix

    // Pass the matrices to the shader
    shader.setUniform("model", model);
    shader.setUniform("view", view);
    shader.setUniform("projection", projection);


    // Main loop
    auto previousTime = std::chrono::high_resolution_clock::now();
    while (!window.shouldClose()) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        // Calculate deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, camera, deltaTime);

        glm::mat4 view = camera.getViewMatrix();
        shader.setUniform("view", view);


        // Bind the VAO and EBO, and draw the cube
        vao.bind();
        ebo.bind();
        shader.use();
        glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, nullptr);

        window.swapBuffers();
    }

    return 0;
}

void processInput(Window& window, Camera& camera, float deltaTime) {
    if (window.isKeyPressed(GLFW_KEY_W))
        camera.processKeyboard(FORWARD, deltaTime);
    if (window.isKeyPressed(GLFW_KEY_S))
        camera.processKeyboard(BACKWARD, deltaTime);
    if (window.isKeyPressed(GLFW_KEY_A))
        camera.processKeyboard(LEFT, deltaTime);
    if (window.isKeyPressed(GLFW_KEY_D))
        camera.processKeyboard(RIGHT, deltaTime);
    if (window.isKeyPressed(GLFW_KEY_SPACE))
        camera.processKeyboard(UP, deltaTime);
    if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
        camera.processKeyboard(DOWN, deltaTime);
}

// Mouse movement callback
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    static float lastX = 800.0f / 2.0; // Assuming window width of 800
    static float lastY = 600.0f / 2.0; // Assuming window height of 600
    static bool firstMouse = true;

    if (firstMouse) { // This avoids the initial jump
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    // Update camera rotation
    camera->processMouseMovement(xoffset, yoffset);
}