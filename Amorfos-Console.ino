#include "Arduino.h"
#include <stdbool.h>
#include <SPI.h>
#include "src/framework/thirdparty/TFT_ILI9163C/TFT_ILI9163C.h"

#include "src/framework/amorfos.h"

#define __CS1 	10
#define __DC 	9

#if defined(TFT_ILI9163C_INSTANCES)
TFT_ILI9163C tft = TFT_ILI9163C(REDPCB_NEW, __CS1, __DC);
#else
TFT_ILI9163C tft = TFT_ILI9163C(__CS1, __DC);
#endif

amorfos::Input input;
float time = 0;

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
    // setup LED output
    DDRB |= (1 << LED0);
    DDRB |= (1 << LED1);
    // lcd setup
    tft.begin();
    amorfos::start();
}

void loop() {
    // update time
    float oldTime = time;
    time = millis() / 1000.0f;
    float deltaTime = time - oldTime;
    amorfos::update(deltaTime);
    amorfos_internal::render(amorfos::getEntities(), amorfos::getEntityCount(), &tft);
    amorfos_internal::checkCollisions(amorfos::getEntities(), amorfos::getEntityCount());
    // update joystick input
    input.joystickY = analogRead(A0) / 1023.0f;
    input.joystickX = analogRead(A1) / 1023.0f;
}