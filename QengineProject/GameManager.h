#include <memory>

#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Transform.h"
#include "InputManager.h"
#include "ImGuiManager.h"

#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "CameraSystem.h"

// ECS
#include "ComponentManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "../../components/RenderComponent.h"
#include "../../components/TransformComponent.h"
#include "../../components/VelocityComponent.h"
#include "../../components/InputComponent.h"
#include "../../components/CameraComponent.h"

class GameManager {
public:
    GameManager();                     // Constructor to initialize components
    void init();                       // Initializes all systems
    void run();                        // Main game loop
    void shutdown();                   // Cleans up resources

    std::shared_ptr<Camera> camera;
    std::shared_ptr<Window> window;

private:
    void update();                     // Updates game logic
    void render();                     // Renders the scene
    void processInput();               // Handles input processing

    std::shared_ptr<InputManager> inputManager;
    std::shared_ptr<ImGuiManager> imguiManager;
    std::shared_ptr<Transform> transform;

    std::shared_ptr<Model> model;

    std::shared_ptr<Shader> shader;

    // ECS
    EntityManager entityManager;
    Entity entity;
    ComponentManager<TransformComponent> transformManager;
    ComponentManager<RenderComponent> renderManager;
    ComponentManager<VelocityComponent> velocityManager;
    ComponentManager<InputComponent> inputManagerComponent;
    ComponentManager<CameraComponent> cameraManager;

    std::shared_ptr<PhysicsSystem> physicsSystem;
    std::shared_ptr<InputSystem> inputSystem;
    std::shared_ptr<CameraSystem> cameraSystem;


    float lastFrameTime = 0.0f;
};
