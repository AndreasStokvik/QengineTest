#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"
#include "InputManager.h"
#include "Model.h"
#include "ImGuiManager.h"
#include <memory>

class GameManager {
public:
    GameManager();                     // Constructor to initialize components
    void init();                       // Initializes all systems
    void run();                        // Main game loop
    void shutdown();                   // Cleans up resources

private:
    void update();                     // Updates game logic
    void render();                     // Renders the scene
    void processInput();               // Handles input processing

    // Member variables for components
    std::shared_ptr<Window> window;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<InputManager> inputManager;
    std::shared_ptr<ImGuiManager> imguiManager;
    std::shared_ptr<Transform> transform;
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;

    float lastFrameTime = 0.0f;
};
