#include "amorfos.h"

#include <stdlib.h>

amorfos::Entity* amorfos::CreateEntity() {
    // create
    Entity* entity = newEntity();
    // add to list
    entities = (Entity**)realloc(entities, sizeof(Entity*) * (entityCount + 1));
    entities[entityCount] = entity;
    entityCount++;
    return entity;
}

void amorfos::DestroyEntity(Entity* entity) {
    for (int i = 0; i < entityCount; i++) {
        if (entities[i] == entity) {
            entities[i] = entities[entityCount - 1];
            entityCount--;
            free(entity);
            break;
        }
    }
}