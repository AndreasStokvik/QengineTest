#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"
#include "InputManager.h"
#include "Model.h"
#include "ImGuiManager.h"
#include <memory>

int main() {
    std::shared_ptr<Window> window = std::make_shared<Window>(800, 600, "OpenGL Window");
    std::shared_ptr<InputManager> inputManager = std::make_shared<InputManager>();
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    
    inputManager->setMouseCallback(window, camera);

    float deltaTime, lastFrame = 0.0f;

    std::shared_ptr<ImGuiManager> imgui = std::make_shared<ImGuiManager>(window);
    std::shared_ptr<Model> model = std::make_shared<Model>("models/cube2.obj");
    std::shared_ptr<Shader> shader = std::make_shared<Shader>("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    std::shared_ptr<Transform> transform = std::make_shared<Transform>(camera, window, shader);

    shader->use();
    transform->setTransformUniforms(shader);
    shader->setLightingUniforms(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f), camera->getPosition());

    while (!window->shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        inputManager->processInput(window, camera, deltaTime);
        transform->update(camera, window, shader);

        model->draw(shader);
        imgui->BasicText("Title", "text");

        window->swapBuffers();
    }
    imgui->shutdown();
    glfwTerminate();
    return 0;
}