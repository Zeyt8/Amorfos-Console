#include "rendering.h"

#include "Arduino.h"

void amorfos_internal::render(amorfos::Entity** entities, int entityCount, Ucglib_ILI9341_18x240x320_SWSPI* ucg) {
    ucg->clearScreen();
    for (int i = 0; i < entityCount; i++) {
        amorfos::Entity* entity = entities[i];
        if (entity->isVisible && entity->graphics != 0 && !entity->isDestroyed) {
            ucg->setColor(entity->color.x, entity->color.y, entity->color.z);
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    if ((entity->graphics >> (x * 3 + y)) & 1) {
                        ucg->drawPixel(entity->position.y + y - 1, entity->position.x + x - 1);
                    }
                }
            }
        }
    }
}

void amorfos::setLED(bool on, int led)
{
    if (led == 0) {
        if (on) {
            PORTD |= (1 << LED0);
        }
        else {
            PORTD &= ~(1 << LED0);
        }
    }
    else if (led == 1) {
        if (on) {
            PORTD |= (1 << LED1);
        }
        else {
            PORTD &= ~(1 << LED1);
        }
    }
}