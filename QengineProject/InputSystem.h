#pragma once
#include <iostream>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "EntityManager.h"
#include "ComponentManager.h"
#include "../../components/InputComponent.h"
#include "../../components/VelocityComponent.h"
#include "InputManager.h"

class InputSystem {
public:
    InputSystem(EntityManager& entityManager,
        ComponentManager<InputComponent>& inputComponents,
        ComponentManager<VelocityComponent>& velocityComponents,
        std::shared_ptr<InputManager> inputManagerInstance)
        : entityManager(entityManager),
        inputComponents(inputComponents),
        velocityComponents(velocityComponents),
        inputManagerInstance(std::move(inputManagerInstance)) {}

    void update(const std::shared_ptr<Window>& window, float deltaTime) {

        for (int entity : entityManager.getEntities()) {
            if (inputComponents.hasComponent(entity) && velocityComponents.hasComponent(entity)) {
                InputComponent& inputComp = inputComponents.getComponent(entity);
                VelocityComponent& velocityComp = velocityComponents.getComponent(entity);

                inputComp.movementDirection = glm::vec3(0.0f);

                glm::vec3 direction = inputManagerInstance->getMovementDirection(window);
                inputComp.movementDirection = direction;

                // NaN value check
                if (glm::any(glm::isnan(inputComp.movementDirection))) {
                    inputComp.movementDirection = glm::vec3(0.0f); // Reset to zero if NaN
                }
                else {
                    if (glm::length(inputComp.movementDirection) > 0.0f) {
                        inputComp.movementDirection = glm::normalize(inputComp.movementDirection);
                    }
                }
                velocityComp.velocity = inputComp.movementDirection * desiredSpeed;
            }
        }
    }

private:
    EntityManager& entityManager;
    ComponentManager<InputComponent>& inputComponents;
    ComponentManager<VelocityComponent>& velocityComponents;
    std::shared_ptr<InputManager> inputManagerInstance;
    float desiredSpeed = 5.0f; // Movement speed
};
