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
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    std::unique_ptr<InputManager> inputManager = std::make_unique<InputManager>(window, camera);

    std::unique_ptr<ImGuiManager> imgui = std::make_unique<ImGuiManager>(window);
    std::shared_ptr<Model> model = std::make_shared<Model>("models/cube2.obj");
    std::shared_ptr<Shader> shader = std::make_shared<Shader>("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl", camera);
    std::shared_ptr<Transform> transform = std::make_shared<Transform>(camera, window, shader);

    while (!window->shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        inputManager->processInput(window, camera);
        transform->update(camera, window, shader);

        model->draw(shader);
        imgui->BasicText("Title", "text");

        window->swapBuffers();
    }
    imgui->shutdown();
    glfwTerminate();
    return 0;
}