#include "rendering.h"

void amorfos_internal::render(amorfos::Entity** entities, int entityCount) {
    for (int i = 0; i < entityCount; i++) {
        amorfos::Entity* entity = entities[i];
        if (entity->isVisible) {
            // render entity
        }
    }
}