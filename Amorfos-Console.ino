#include "arduino.h"
#include <stdbool.h>

#include "src/framework/amorfos.h"

amorfos::Entity** entities;
unsigned int entityCount;
amorfos::Input input;
float time;

// button north
ISR(PCINT18_vect) {
    if (input.buttonNorth) {
        input.buttonNorth = false;
        amorfos::onButtonRelease(BUTTON_NORTH);
    } else {
        input.buttonNorth = true;
        amorfos::onButtonPress(BUTTON_NORTH);
    }
}

// button east
ISR(PCINT19_vect) {
    if (input.buttonEast) {
        input.buttonEast = false;
        amorfos::onButtonRelease(BUTTON_EAST);
    } else {
        input.buttonEast = true;
        amorfos::onButtonPress(BUTTON_EAST);
    }
}

// button south
ISR(PCINT20_vect) {
    if (input.buttonSouth) {
        input.buttonSouth = false;
        amorfos::onButtonRelease(BUTTON_SOUTH);
    } else {
        input.buttonSouth = true;
        amorfos::onButtonPress(BUTTON_SOUTH);
    }
}

// button east
ISR(PCINT21_vect) {
    if (input.buttonWest) {
        input.buttonWest = false;
        amorfos::onButtonRelease(BUTTON_WEST);
    } else {
        input.buttonWest = true;
        amorfos::onButtonPress(BUTTON_WEST);
    }
}

// button joystick
ISR(PCINT22_vect) {
    if (input.buttonJoystick) {
        input.buttonJoystick = false;
        amorfos::onButtonRelease(BUTTON_JOYSTICK);
    } else {
        input.buttonJoystick = true;
        amorfos::onButtonPress(BUTTON_JOYSTICK);
    }
}

void setup() {
    // setup intrerrupts for buttons
    cli();
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22);
    sei();
    // setup joystick input
    DDRD &= ~(1 << PD0);
    DDRD &= ~(1 << PD1);
    amorfos::start();
}

void loop() {
    // update time
    float oldTime = time;
    time = millis() / 1000.0f;
    float deltaTime = time - oldTime;
    amorfos::update(deltaTime);
    amorfos_internal::render(entities, entityCount);
    amorfos_internal::checkCollisions(entities, entityCount);
    // update joystick input
    input.joystickY = (PIND & (1 << PD0)) / 1023.0f;
    input.joystickX = (PIND & (1 << PD1)) / 1023.0f;
}