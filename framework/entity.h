#pragma once

#include <stdlib.h>
#include "vector.h"

typedef struct Entity {
    unsigned int type;
    Vector2 position;
    struct Entity **children;
    unsigned int childCount;
    struct Entity *parent;
    Vector3 color;
    bool isVisible;
} Entity;

/// @brief Increases the enitity's position by the given x and y values
/// @param entity The entity to move
/// @param x 
/// @param y 
void move(Entity* entity, int x, int y) {
    entity->position.x += x;
    entity->position.y += y;
    // move children as well
    for (int i = 0; i < entity->childCount; i++) {
        move(entity->children[i], x, y);
    }
}

/// @brief Sets the enitity's position to the given x and y values
/// @param entity The entity to move
/// @param x 
/// @param y 
void setPosition(Entity* entity, int x, int y) {
    entity->position.x = x;
    entity->position.y = y;
    // move children as well, keeping relative position
    for (int i = 0; i < entity->childCount; i++) {
        move(entity->children[i], x - entity->children[i]->position.x, y - entity->children[i]->position.y);
    }
}

/// @brief Sets the enitity's color to the given r, g and b values
/// @param entity The entity to change the color of
/// @param r 
/// @param g 
/// @param b 
void setColor(Entity* entity, float r, float g, float b) {
    entity->color.x = r;
    entity->color.y = g;
    entity->color.z = b;
}

/// @brief Sets the enitity's parent to the given parent. Adds the enitity to the parent's children. If parent is NULL, removes the previous parenting of the enitity.
/// @param entity The entity to change the parent of
/// @param parent The new parent of the entity
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