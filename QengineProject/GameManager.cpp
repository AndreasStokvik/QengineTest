#include "GameManager.h"
GameManager::GameManager() {}

void GameManager::init() {
    window = std::make_shared<Window>(800, 600, "OpenGL Window");
    camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    inputManager = std::make_shared<InputManager>(window, camera);
    imguiManager = std::make_shared<ImGuiManager>(window);
    model = std::make_shared<Model>("models/cube2.obj");
    shader = std::make_shared<Shader>("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl", camera);
    transform = std::make_shared<Transform>(camera, window, shader);

    shader->use();
    transform->setTransformUniforms(shader);
    shader->setLightingUniforms(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f), camera->getPosition());
}

void GameManager::run()
{
    while (!window->shouldClose()) {
        glfwPollEvents();
        processInput();
        update();
        render();

        window->swapBuffers();
    }
    shutdown();
}

void GameManager::processInput()
{
    inputManager->processInput(window, camera);
}

void GameManager::update() {
    transform->update(camera, window, shader);
}

void GameManager::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    model->draw(shader);

    imguiManager->BasicText("Title", "text");
}

void GameManager::shutdown() {
    imguiManager->shutdown();
    glfwTerminate();
}