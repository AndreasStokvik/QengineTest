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
    window = std::make_shared<Window>(1280, 720, "OpenGL Window");
    window->setResizeCallback(framebuffer_size_callback);
    camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, window);
    inputManager = std::make_shared<InputManager>(window, camera);
    imguiManager = std::make_shared<ImGuiManager>(window);
    model = std::make_shared<Model>("models/test1.obj");


    // Entity creation  --------------------------------------------------------------------------------------------------
    int entityId = entityManager.createEntity();
    transformManager.addComponent(entityId, TransformComponent(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    auto modelPtr1 = std::make_shared<Model>("models/cube2.obj");
    renderManager.addComponent(entityId, RenderComponent(modelPtr1));

    int entity2 = entityManager.createEntity();
    transformManager.addComponent(entity2, TransformComponent(glm::vec3(10.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.5f)));
    auto modelPtr2 = std::make_shared<Model>("models/test1.obj");
    renderManager.addComponent(entity2, RenderComponent(modelPtr2));

    int entity3 = entityManager.createEntity();
    transformManager.addComponent(entity3, TransformComponent(glm::vec3(2.0f, -5.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.12f)));
    auto modelPtr3 = std::make_shared<Model>("models/environment.obj");
    renderManager.addComponent(entity3, RenderComponent(modelPtr3));

    int entityId4 = entityManager.createEntity();
    transformManager.addComponent(entityId4, TransformComponent(glm::vec3(-20.0f, 10.0f, -20.0f), glm::vec3(45.0f, 0.0f, 45.0f), glm::vec3(10.0f)));
    renderManager.addComponent(entityId4, RenderComponent(modelPtr1));
    //  ------------------------------------------------------------------------------------------------------------------


    shader = std::make_shared<Shader>("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl", camera);
    transform = std::make_shared<Transform>(camera, shader);

    shader->use();
    camera->setProjectionUniform(shader);
    transform->setViewUniform(shader);
    shader->setLightingUniforms(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 10.0f, 2.0f), camera->getPosition());
}

void GameManager::run()
{
    while (!window->shouldClose()) {
        glfwPollEvents();
        processInput();
        camera->updateProjectionMatrix(window);
        render();

        window->swapBuffers();
    }
    shutdown();
}

void GameManager::update() {
    transform->updateViewMatrix(camera);
    transform->setViewUniform(shader);
    for (int entity : entityManager.getEntities()) {
        if (transformManager.hasComponent(entity)) {
            TransformComponent& transformComp = transformManager.getComponent(entity);
            transform->update(transformComp, shader);
        }
    }
}

void GameManager::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();
    update();

    for (int entity : entityManager.getEntities()) {
        if (transformManager.hasComponent(entity)) {
            TransformComponent& transformComp = transformManager.getComponent(entity);
            transform->update(transformComp, shader);

            if (renderManager.hasComponent(entity)) {
                RenderComponent& renderComp = renderManager.getComponent(entity);
                renderComp.model->draw(shader);
            }
        }
    }

    //imguiManager->BasicText("Title", "text");
    //model->draw(shader);
}

void GameManager::shutdown() {
    imguiManager->shutdown();
    glfwTerminate();
}

void GameManager::processInput() { 
    inputManager->processInput(window, camera); 
}