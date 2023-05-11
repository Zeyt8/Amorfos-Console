#include "physics.h"

void amorfos_internal::checkCollisions(amorfos::Entity** entities, int entityCount) {
    for (int i = 0; i < entityCount; i++) {
        for (int j = i + 1; j < entityCount; j++) {
            if (entities[i]->hasCollision && entities[j]->hasCollision) {
                onCollision(entities[i], entities[j]);
            }
        }
    }
}