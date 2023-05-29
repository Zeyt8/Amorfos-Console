#include "Arduino.h"
#include <stdbool.h>
#include <SPI.h>
#include "Ucglib.h"

#include "src/framework/amorfos.h"

using namespace amorfos;
using namespace amorfos_internal;

Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 12);

float time = 0;
volatile int debouncing = 0;
float timeToRender = 0;

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
    }
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
    // setup intrerrupts for buttons
    DDRD &= ~(1 << BUTTON_TOP) & ~(1 << BUTTON_RIGHT) & ~(1 << BUTTON_BOTTOM) & ~(1 << BUTTON_LEFT);
    DDRB &= ~(1 << BUTTON_JOYSTICK);
    PORTD |= (1 << BUTTON_TOP) | (1 << BUTTON_RIGHT) | (1 << BUTTON_BOTTOM) | (1 << BUTTON_LEFT);
    PORTB |= (1 << BUTTON_JOYSTICK);
    PCICR |= (1 << PCIE2) | (1 << PCIE0);
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21);
    PCMSK0 |= (1 << PCINT0);
    // setup LED output
    DDRD |= (1 << LED0);
    DDRD |= (1 << LED1);
    // setup buzzer
    DDRD |= (1 << BUZZER);
    sei();
    // lcd setup
    ucg.begin(UCG_FONT_MODE_TRANSPARENT);
    ucg.setFont(ucg_font_ncenR12_tr);
    ucg.setScale2x2();
    ucg.clearScreen();
    timeToRender = renderUpdateFrequency;
    start();
}

static void handleJoystick() {
    input.joystickX = analogRead(A4);
    input.joystickY = analogRead(A5);
    if (input.joystickX > 600) {
        input.joystickX = -1;
    }
    else if (input.joystickX < 400) {
        input.joystickX = 1;
    }
    else {
        input.joystickX = 0;
    }
    if (input.joystickY > 600) {
        input.joystickY = -1;
    }
    else if (input.joystickY < 400) {
        input.joystickY = 1;
    }
    else {
        input.joystickY = 0;
    }
}

void loop() {
    // update time
    float oldTime = time;
    time = millis() / 1000.0f;
    float deltaTime = time - oldTime;
    update(deltaTime);
    if (renderUpdateFrequency < 0) {
        render(entities, entityCount, &ucg);
    }
    else {
        timeToRender += deltaTime;
        if (timeToRender >= renderUpdateFrequency) {
            render(entities, entityCount, &ucg);
            timeToRender = 0;
        }
    }
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
    handleJoystick();
    // restart if required
    if (toRestart) {
        for (int i = entityCount; i >= 0; i--) {
            destroyEntity(entities[i]);
        }
        start();
    }
}