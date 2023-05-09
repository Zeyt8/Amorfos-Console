#include <stdbool.h>

#include "framework/input.h"
#include "framework/entity.h"
#include "framework/rendering.h"
#include "framework/audio.h"
#include "framework/vector.h"

Entity** entities;
unsigned int entityCount;
Input input;
float time;

/// @brief Called at the start of the game
void Start();
/// @brief The main game loop. Delta time is the time since the last frame
/// @param deltaTime 
void Update(float deltaTime);

/// @brief Create an entity
/// @return The created entity
Entity* CreateEntity() {
    // create
    Entity* entity = malloc(sizeof(Entity));
    entity->type = 0;
    entity->position = newVector2(0, 0);
    entity->children = NULL;
    entity->childCount = 0;
    entity->parent = NULL;
    entity->color = newVector3(1, 1, 1);
    entity->isVisible = true;
    // add to list
    entities = realloc(entities, sizeof(Entity*) * (entityCount + 1));
    entities[entityCount] = entity;
    entityCount++;
    return entity;
}
/// @brief Destroy an entity
void DestroyEntity(Entity* entity) {
    for (int i = 0; i < entityCount; i++) {
        if (entities[i] == entity) {
            entities[i] = entities[entityCount - 1];
            entityCount--;
            break;
        }
    }
}