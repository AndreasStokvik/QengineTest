#include "Camera.h"
#include "Window.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Transform {
public:
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    Transform(const std::shared_ptr<Camera>& camera, const std::shared_ptr <Window>& window, const std::shared_ptr<Shader>& shader);

    void update(const std::shared_ptr<Camera>& camera, const std::shared_ptr <Window>& window, const std::shared_ptr<Shader>& shader);

    void setTransformUniforms(const std::shared_ptr<Shader>& shader);
};
