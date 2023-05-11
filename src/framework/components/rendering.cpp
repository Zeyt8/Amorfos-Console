#include "rendering.h"
#include "../thirdparty/TFT_ILI9163C/TFT_ILI9163C.h"

void amorfos_internal::render(amorfos::Entity** entities, int entityCount, TFT_ILI9163C* tft) {
    for (int i = 0; i < entityCount; i++) {
        amorfos::Entity* entity = entities[i];
        if (entity->isVisible) {
            // render entity
        }
    }
}