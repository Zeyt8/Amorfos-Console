#include "rendering.h"

#include "Arduino.h"

void amorfos_internal::render(amorfos::Entity** entities, int entityCount, TFT_ILI9163C* tft) {
    tft->clearScreen();
    for (int i = 0; i < entityCount; i++) {
        amorfos::Entity* entity = entities[i];
        if (entity->isVisible) {
            tft->drawPixel(entity->position.x, entity->position.y, entity->color);
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