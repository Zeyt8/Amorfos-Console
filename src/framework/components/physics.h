#include "entity.h"

namespace amorfos_internal
{
    void checkCollisions(amorfos::Entity** entities, int entityCount);
}

namespace amorfos
{
    extern void onCollision(Entity* entity1, Entity* entity2);
}