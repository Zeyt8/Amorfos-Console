#include "entity.h"

namespace amorfos_internal
{
    void checkCollisions(amorfos::Entity** entities, int entityCount);
}

namespace amorfos
{
    /// @brief Called when 2 entities collide. It is only called if both entities have collision enabled.
    /// @param entity1 The first entity that is part of the collision
    /// @param entity2 The second entity that is part of the collision
    extern void onCollision(Entity* entity1, Entity* entity2);
}