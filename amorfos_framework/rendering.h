#include "entity.h"

void render(Entity** entities, int entityCount) {
    for (int i = 0; i < entityCount; i++) {
        Entity* entity = entities[i];
        if (entity->isVisible) {
            // render entity
        }
    }
}