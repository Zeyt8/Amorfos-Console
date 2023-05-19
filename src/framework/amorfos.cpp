#include "amorfos.h"

#include <stdlib.h>

amorfos::Entity** entities;
unsigned int entityCount;

amorfos::Entity* amorfos::createEntity(int type, Vector2 position, Vector3 color, bool isVisible, bool hasCollision, void* data) {
    // create
    Entity* entity = newEntity(type, position, color, isVisible, hasCollision, data);
    // add to list
    entities = (Entity**)realloc(entities, sizeof(Entity*) * (entityCount + 1));
    entities[entityCount] = entity;
    entityCount++;
    return entity;
}

void amorfos::destroyEntity(Entity* entity) {
    for (int i = 0; i < entityCount; i++) {
        if (entities[i] == entity) {
            entities[i] = entities[entityCount - 1];
            entityCount--;
            free(entity);
            break;
        }
    }
}

amorfos::Entity** amorfos::getEntities() {
    return entities;
}

unsigned int amorfos::getEntityCount() {
    return entityCount;
}