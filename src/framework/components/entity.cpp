#include "entity.h"

#include <stdlib.h>

using namespace amorfos;

void move(Entity* entity, int x, int y) {
    entity->position.x += x;
    entity->position.y += y;
    // move children as well
    for (int i = 0; i < entity->childCount; i++) {
        amorfos::move(entity->children[i], x, y);
    }
}

void setPosition(Entity* entity, int x, int y) {
    entity->position.x = x;
    entity->position.y = y;
    // move children as well, keeping relative position
    for (int i = 0; i < entity->childCount; i++) {
        amorfos::move(entity->children[i], x - entity->children[i]->position.x, y - entity->children[i]->position.y);
    }
}

void setColor(Entity* entity, float r, float g, float b) {
    entity->color.x = r;
    entity->color.y = g;
    entity->color.z = b;
}

void parent(Entity* entity, Entity* parent) {
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