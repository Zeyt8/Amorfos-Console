#include "rendering.h"

void amorfos_internal::render(amorfos::Entity** entities, int entityCount, TFT_ILI9163C* tft) {
    tft->clearScreen();
    for (int i = 0; i < entityCount; i++) {
        amorfos::Entity* entity = entities[i];
        if (entity->isVisible) {
            tft->drawPixel(entity->position.x, entity->position.y, entity->color);
        }
    }
}