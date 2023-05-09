#pragma once

#include <stdbool.h>

#include "components/input.h"
#include "components/entity.h"
#include "components/rendering.h"
#include "components/audio.h"
#include "utils/vector.h"

extern Entity** entities;
extern unsigned int entityCount;
extern Input input;

/// @brief Called at the start of the game
void Start();

/// @brief The main game loop. Delta time is the time since the last frame
/// @param deltaTime 
void Update(float deltaTime);

/// @brief Create an entity
/// @return The created entity
Entity* CreateEntity();

/// @brief Destroy an entity
void DestroyEntity(Entity* entity);