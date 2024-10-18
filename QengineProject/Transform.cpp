#include "Transform.h"

Transform::Transform(const std::shared_ptr<Camera>& camera, const std::shared_ptr <Window>& window, const std::shared_ptr<Shader>& shader) {
    model = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), window->getAspectRatio(), 0.1f, 100.0f);
    update(camera, window, shader);
    setTransformUniforms(shader);
}

void Transform::update(const std::shared_ptr<Camera>& camera, const std::shared_ptr <Window>& window, const std::shared_ptr<Shader>& shader) {
    view = camera->getViewMatrix();
    setTransformUniforms(shader);
}

void Transform::setTransformUniforms(const std::shared_ptr<Shader>& shader)
{
    shader->setUniform("model", model);
    shader->setUniform("view", view);
    shader->setUniform("projection", projection);
}
