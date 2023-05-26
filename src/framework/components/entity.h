#pragma once

#include "../utils/vector.h"

namespace amorfos
{
    typedef struct Entity {
        unsigned int type;  // a tag you can assign to the object to identify its type
        Vector2<int> position;   // the position of the object
        struct Entity **children;   // the children of the object
        unsigned int childCount;    // the number of children the object has
        struct Entity *parent;  // the parent of the object
        Vector3<int> color;  // the color of the object
        bool isVisible; // whether the object is visible or not
        bool hasCollision;  // whether the object has collision or not
        void *data; // a pointer to any data you want to attach to the object
    } Entity;

    /// @brief Creates a new entity
    Entity* newEntity(int type=0, Vector2<int> position=newVector2(0, 0), Vector3<int> color=newVector3(1, 1, 1), bool isVisible=true, bool hasCollision=false, void* data=nullptr);

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
    void setColor(Entity* entity, int r, int g, int b);

    /// @brief Sets the enitity's parent to the given parent. Adds the enitity to the parent's children. If parent is NULL, removes the previous parenting of the enitity.
    /// @param entity The entity to change the parent of
    /// @param parent The new parent of the entity
    void parent(Entity* entity, Entity* parent);
}