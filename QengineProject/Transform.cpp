#include "Transform.h"

Transform::Transform(Camera& camera, Window& window) {
    model = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f);
    update(camera, window);
}

void Transform::update(Camera& camera, Window& window) {
    view = camera.getViewMatrix();
}