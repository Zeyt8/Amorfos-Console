#include "rendering.h"

#include "Arduino.h"

void amorfos_internal::render(amorfos::Entity** entities, int entityCount, Ucglib_ILI9163_18x128x128_SWSPI* ucg) {
    ucg->clearScreen();
    for (int i = 0; i < entityCount; i++) {
        amorfos::Entity* entity = entities[i];
        if (entity->isVisible) {
            ucg->setColor(entity->color.x, entity->color.y, entity->color.z);
            ucg->drawPixel(entity->position.x, entity->position.y);
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