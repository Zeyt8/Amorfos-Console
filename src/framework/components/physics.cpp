#include "physics.h"
#include "Arduino.h"

// cache sqrt values for numbers less that 10
static int sqrtCache[10] = { 0, 1, 1, 2, 2, 2, 2, 2, 3, 3 };

void amorfos_internal::checkCollisions(amorfos::Entity** entities, int entityCount) {
    for (int i = 0; i < entityCount; i++) {
        for (int j = i + 1; j < entityCount; j++) {
            if (entities[i]->hasCollision && entities[j]->hasCollision && !entities[i]->isDestroyed && !entities[j]->isDestroyed) {
                // check collision radiuses. Radius of 0 means only check for exact position match
                if (entities[i]->collisionRadius == 0 && entities[j]->collisionRadius == 0) {
                    if (entities[i]->position.x == entities[j]->position.x && entities[i]->position.y == entities[j]->position.y) {
                        amorfos::onCollision(entities[i], entities[j]);
                    }
                }
                else {
                    // check collision radiuses
                    int dx = entities[i]->position.x - entities[j]->position.x;
                    int dy = entities[i]->position.y - entities[j]->position.y;
                    // use cache for sqrt if possible
                    int distance = 0;
                    int sqdistance = dx * dx + dy * dy;
                    if (sqdistance < 10) {
                        distance = sqrtCache[sqdistance];
                    }
                    else {
                        distance = sqrt(sqdistance);
                    }
                    if (distance <= entities[i]->collisionRadius + entities[j]->collisionRadius) {
                        amorfos::onCollision(entities[i], entities[j]);
                    }
                }
            }
        }
    }
}