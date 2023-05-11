#include "physics.h"

void amorfos_internal::checkCollisions(amorfos::Entity** entities, int entityCount) {
    for (int i = 0; i < entityCount; i++) {
        for (int j = i + 1; j < entityCount; j++) {
            if (entities[i]->hasCollision && entities[j]->hasCollision &&
                entities[i]->position.x == entities[j]->position.x && entities[i]->position.y == entities[j]->position.y) {
                onCollision(entities[i], entities[j]);
            }
        }
    }
}