#include "amorfos.h"

#include <stdlib.h>

Entity* CreateEntity() {
    // create
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    entity->type = 0;
    entity->position = newVector2(0, 0);
    entity->children = NULL;
    entity->childCount = 0;
    entity->parent = NULL;
    entity->color = newVector3(1, 1, 1);
    entity->isVisible = true;
    // add to list
    entities = (Entity**)realloc(entities, sizeof(Entity*) * (entityCount + 1));
    entities[entityCount] = entity;
    entityCount++;
    return entity;
}

void DestroyEntity(Entity* entity) {
    for (int i = 0; i < entityCount; i++) {
        if (entities[i] == entity) {
            entities[i] = entities[entityCount - 1];
            entityCount--;
            break;
        }
    }
}