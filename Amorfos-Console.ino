#include "Arduino.h"
#include <stdbool.h>
#include <SPI.h>
#include "Ucglib.h"

#include "src/framework/amorfos.h"

using namespace amorfos;
using namespace amorfos_internal;

Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 12);

float time = 0;
volatile int debouncing = 0;

ISR(PCINT2_vect) {
    if (millis() - debouncing < 100) return;
    debouncing = millis();
    if ((PIND & (1 << BUTTON_TOP)) == 0) {
        if (input.buttonNorth) {
            input.buttonNorth = false;
            onButtonRelease(BUTTON_TOP);
        } else {
            input.buttonNorth = true;
            onButtonPress(BUTTON_TOP);
        }
    } else if ((PIND & (1 << BUTTON_RIGHT)) == 0) {
        if (input.buttonWest) {
            input.buttonWest = false;
            onButtonRelease(BUTTON_RIGHT);
        } else {
            input.buttonWest = true;
            onButtonPress(BUTTON_RIGHT);
        }
    } else if ((PIND & (1 << BUTTON_BOTTOM)) == 0) {
        if (input.buttonSouth) {
            input.buttonSouth = false;
            onButtonRelease(BUTTON_BOTTOM);
        } else {
            input.buttonSouth = true;
            onButtonPress(BUTTON_BOTTOM);
        }
    } else if ((PIND & (1 << BUTTON_LEFT)) == 0) {
        if (input.buttonEast) {
            input.buttonEast = false;
            onButtonRelease(BUTTON_LEFT);
        } else {
            input.buttonEast = true;
            onButtonPress(BUTTON_LEFT);
        }
    }/* else if ((PIND & (1 << BUTTON_START)) == 0) {
        if (input.buttonStart) {
            input.buttonStart = false;
            onButtonRelease(BUTTON_START);
        } else {
            input.buttonStart = true;
            onButtonPress(BUTTON_START);
        }
    } else if ((PIND & (1 << BUTTON_SELECT)) == 0) {
        if (input.buttonSelect) {
            input.buttonSelect = false;
            onButtonRelease(BUTTON_SELECT);
        } else {
            input.buttonSelect = true;
            onButtonPress(BUTTON_SELECT);
        }
    }*/
}

ISR(PCINT0_vect) {
    if (millis() - debouncing < 100) return;
    debouncing = millis();
    if ((PINB & (1 << (BUTTON_JOYSTICK - 8))) == 0) {
        if (input.buttonJoystick) {
            input.buttonJoystick = false;
            onButtonRelease(BUTTON_JOYSTICK);
        } else {
            input.buttonJoystick = true;
            onButtonPress(BUTTON_JOYSTICK);
        }
    }
}

void setup() {
    delay(1000);
    cli();
    // setup input
    // setup intrerrupts for buttons
    DDRD &= ~(1 << BUTTON_TOP) & ~(1 << BUTTON_RIGHT) & ~(1 << BUTTON_BOTTOM) & ~(1 << BUTTON_LEFT)/* & ~(1 << BUTTON_START) & ~(1 << BUTTON_SELECT)*/;
    DDRB &= ~(1 << BUTTON_JOYSTICK);
    PORTD |= (1 << BUTTON_TOP) | (1 << BUTTON_RIGHT) | (1 << BUTTON_BOTTOM) | (1 << BUTTON_LEFT)/* | (1 << BUTTON_START) | (1 << BUTTON_SELECT)*/;
    PORTB |= (1 << BUTTON_JOYSTICK);
    PCICR |= (1 << PCIE2) | (1 << PCIE0);
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21)/* | (1 << PCINT22) | (1 << PCINT23)*/;
    PCMSK0 |= (1 << PCINT0);
    pinMode(8, INPUT_PULLUP);
    // setup LED output
    DDRD |= (1 << LED0);
    DDRD |= (1 << LED1);
    sei();
    // lcd setup
    ucg.begin(UCG_FONT_MODE_TRANSPARENT);
    ucg.setFont(ucg_font_ncenR12_tr);
    ucg.setScale2x2();
    ucg.clearScreen();
    start();
}

void loop() {
    // update time
    float oldTime = time;
    time = millis() / 1000.0f;
    float deltaTime = time - oldTime;
    update(deltaTime);
    render(entities, entityCount, &ucg);
    checkCollisions(entities, entityCount);
    // destroy required objects
    for (int i = entityCount - 1; i >= 0; i--) {
        if (entities[i]->isDestroyed) {
            entities[i] = entities[entityCount - 1];
            entityCount--;
            free(entities[entityCount]);
        }
    }
    entities = (Entity**)realloc(entities, sizeof(Entity*) * entityCount);
    // update joystick input
    input.joystickX = map(1023.0 - analogRead(A4), 0, 1023.0, -1, 1);
    input.joystickY = map(1023.0 - analogRead(A5), 0, 1023.0, -1, 1);
}