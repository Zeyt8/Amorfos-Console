#include "entity.h"

#include <stdlib.h>

amorfos::Entity* amorfos::newEntity(int type, Vector2<int> position, Vector3<int> color, bool isVisible, bool hasCollision, void* data) {
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    entity->type = type;
    entity->position = position;
    entity->children = NULL;
    entity->childCount = 0;
    entity->parent = NULL;
    entity->color = color;
    entity->graphics = 0;
    entity->isVisible = isVisible;
    entity->hasCollision = hasCollision;
    entity->collisionRadius = 0;
    entity->data = data;
    entity->isDestroyed = false;

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
    // move children, keeping relative position
    for (int i = 0; i < entity->childCount; i++) {
        amorfos::move(entity->children[i], x - entity->position.x, y - entity->position.y);
    }
    // move object
    entity->position.x = x;
    entity->position.y = y;
}

void amorfos::setColor(Entity* entity, int r, int g, int b) {
    entity->color = newVector3<int>(r, g, b);
}

void amorfos::setGraphics(Entity* entity, uint16_t graphics[3][3]) {
    // set graphics bit field
    entity->graphics = 0;
    for (int i = 0; i < 3; i++) {
        int j = 2 - i;
        entity->graphics |= graphics[0][i] << (j * 3 + 2);
        entity->graphics |= graphics[1][i] << (j * 3 + 1);
        entity->graphics |= graphics[2][i] << (j * 3);
    }
}

void amorfos::setCollisionRadius(Entity* entity, int8_t collisionRadius) {
    entity->collisionRadius = collisionRadius;
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