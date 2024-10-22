#include "GameManager.h"
GameManager::GameManager() {}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    GameManager* gameManager = static_cast<GameManager*>(glfwGetWindowUserPointer(window));
    if (gameManager) {
        gameManager->camera->updateProjectionMatrix(gameManager->window);
    }
}

void GameManager::init() {
    window = std::make_shared<Window>(800, 600, "OpenGL Window");
    window->setResizeCallback(framebuffer_size_callback);
    camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, window);
    inputManager = std::make_shared<InputManager>(window, camera);
    imguiManager = std::make_shared<ImGuiManager>(window);
    model = std::make_shared<Model>("models/test1.obj");


    // ECS stuff  --------------------------------------------------------------------------------------------------------
    entity = Entity(1);
    transformManager.addComponent(entity.getId(), TransformComponent(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    renderManager.addComponent(entity.getId(), RenderComponent("models/cube2.obj"));
    //  ------------------------------------------------------------------------------------------------------------------


    shader = std::make_shared<Shader>("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl", camera);
    transform = std::make_shared<Transform>(camera, window, shader);

    shader->use();
    camera->setProjectionUniform(shader);
    transform->setTransformUniforms(shader);
    shader->setLightingUniforms(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f), camera->getPosition());
}

void GameManager::run()
{
    while (!window->shouldClose()) {
        glfwPollEvents();
        processInput();
        update();
        camera->updateProjectionMatrix(window);
        render();

        window->swapBuffers();
    }
    shutdown();
}

void GameManager::update() {
    transform->update(camera, window, shader);
}

void GameManager::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();

    model->draw(shader);
    //imguiManager->BasicText("Title", "text");
}

void GameManager::shutdown() {
    imguiManager->shutdown();
    glfwTerminate();
}

void GameManager::processInput() { 
    inputManager->processInput(window, camera); 
}