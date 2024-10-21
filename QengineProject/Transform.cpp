#include "Transform.h"

Transform::Transform(const std::shared_ptr<Camera>& camera, const std::shared_ptr <Window>& window, const std::shared_ptr<Shader>& shader) {
    model = glm::mat4(1.0f);
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
}