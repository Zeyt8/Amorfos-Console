#include "entity.h"

#include <stdlib.h>

amorfos::Entity* amorfos::newEntity() {
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    entity->type = 0;
    entity->position = newVector2(0, 0);
    entity->children = NULL;
    entity->childCount = 0;
    entity->parent = NULL;
    entity->color = newVector3(1, 1, 1);
    entity->isVisible = true;
    entity->hasCollision = true;
    entity->data = NULL;

    return entity;
}

void amorfos::move(Entity* entity, int x, int y) {
    entity->position.x += x;
    entity->position.y += y;
    // move children as well
    for (int i = 0; i < entity->childCount; i++) {
        move(entity->children[i], x, y);
    }
}

void amorfos::setPosition(Entity* entity, int x, int y) {
    entity->position.x = x;
    entity->position.y = y;
    // move children as well, keeping relative position
    for (int i = 0; i < entity->childCount; i++) {
        amorfos::move(entity->children[i], x - entity->children[i]->position.x, y - entity->children[i]->position.y);
    }
}

void amorfos::setColor(Entity* entity, float r, float g, float b) {
    entity->color.x = r;
    entity->color.y = g;
    entity->color.z = b;
}

void amorfos::parent(Entity* entity, Entity* parent) {
    entity->parent = parent;
    // if parent is null, remove entity from parent
    if (parent == NULL) {
        // find child and remove it from the list
        for (int i = 0; i < parent->childCount; i++) {
            if (parent->children[i] == entity) {
                parent->children[i] = parent->children[parent->childCount - 1];
                parent->childCount--;
                break;
            }
        }
    }
    else {
        parent->childCount++;
        parent->children = (Entity**)realloc(parent->children, parent->childCount * sizeof(Entity*));
        parent->children[parent->childCount - 1] = entity;
    }
}