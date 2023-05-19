#pragma once

#include <stdbool.h>

#include "components/input.h"
#include "components/entity.h"
#include "components/rendering.h"
#include "components/audio.h"
#include "components/physics.h"
#include "utils/vector.h"

namespace amorfos
{
    /// @brief Called at the start of the game
    void start();

    /// @brief The main game loop. Delta time is the time since the last time the loop was called.
    /// @param deltaTime 
    void update(float deltaTime);

    /// @brief Create an entity
    /// @return The created entity
    Entity* createEntity(int type=0, Vector2 position=newVector2(0, 0), Vector3 color=newVector3(1, 1, 1), bool isVisible=true, bool hasCollision=false, void* data=nullptr);

    /// @brief Destroy an entity
    void destroyEntity(Entity* entity);

    Entity** getEntities();

    unsigned int getEntityCount();
}