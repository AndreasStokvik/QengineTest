#include "Camera.h"
#include "Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    Transform(Camera& camera, Window& window);

    void update(Camera& camera, Window& window);
};
