#pragma once

#include "../utils/vector.h"

namespace amorfos
{
    typedef struct Entity {
        unsigned int type;
        Vector2 position;
        struct Entity **children;
        unsigned int childCount;
        struct Entity *parent;
        Vector3 color;
        bool isVisible;
        bool hasCollision;
        void *data;
    } Entity;

    /// @brief Creates a new entity
    Entity* newEntity();

    /// @brief Increases the enitity's position by the given x and y values
    /// @param entity The entity to move
    /// @param x 
    /// @param y 
    void move(Entity* entity, int x, int y);

    /// @brief Sets the enitity's position to the given x and y values
    /// @param entity The entity to move
    /// @param x 
    /// @param y 
    void setPosition(Entity* entity, int x, int y);

    /// @brief Sets the enitity's color to the given r, g and b values
    /// @param entity The entity to change the color of
    /// @param r 
    /// @param g 
    /// @param b 
    void setColor(Entity* entity, float r, float g, float b);

    /// @brief Sets the enitity's parent to the given parent. Adds the enitity to the parent's children. If parent is NULL, removes the previous parenting of the enitity.
    /// @param entity The entity to change the parent of
    /// @param parent The new parent of the entity
    void parent(Entity* entity, Entity* parent);
}