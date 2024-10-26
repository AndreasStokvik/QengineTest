#pragma once
#include "EntityManager.h"
#include "ComponentManager.h"
#include "../../components/TransformComponent.h"
#include "../../components/VelocityComponent.h"
#include <glm/glm.hpp>

class PhysicsSystem {
public:
    PhysicsSystem(EntityManager& entityManager,
        ComponentManager<TransformComponent>& transformManager,
        ComponentManager<VelocityComponent>& velocityManager)
        : entityManager(entityManager), transformManager(transformManager), velocityManager(velocityManager) {}

    void update(float deltaTime) {
        for (int entity : entityManager.getEntities()) {
            if (transformManager.hasComponent(entity) && velocityManager.hasComponent(entity)) {
                TransformComponent& transformComp = transformManager.getComponent(entity);
                VelocityComponent& velocityComp = velocityManager.getComponent(entity);

                // Update position based on velocity and deltaTime
                transformComp.position += velocityComp.velocity * deltaTime;
            }
        }
    }

private:
    EntityManager& entityManager;
    ComponentManager<TransformComponent>& transformManager;
    ComponentManager<VelocityComponent>& velocityManager;
};
