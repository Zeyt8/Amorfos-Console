#include "Arduino.h"
#include <stdbool.h>
#include <SPI.h>
#include "Ucglib.h"

#include "src/framework/amorfos.h"

Ucglib_ILI9163_18x128x128_SWSPI ucg(/*sclk=*/ 10, /*data=*/ 11, /*cd=*/ 12, /*cs=*/ 13, /*reset=*/ 9);

amorfos::Input input;
float time = 0;

ISR(PCINT2_vect) {
    if ((PIND << BUTTON_TOP) == 0) {
        if (input.buttonNorth) {
            input.buttonNorth = false;
            amorfos::onButtonRelease(BUTTON_TOP);
        } else {
            input.buttonNorth = true;
            amorfos::onButtonPress(BUTTON_TOP);
        }
    } else if ((PIND << BUTTON_RIGHT) == 0) {
        if (input.buttonWest) {
            input.buttonWest = false;
            amorfos::onButtonRelease(BUTTON_RIGHT);
        } else {
            input.buttonWest = true;
            amorfos::onButtonPress(BUTTON_RIGHT);
        }
    } else if ((PIND << BUTTON_BOTTOM) == 0) {
        if (input.buttonSouth) {
            input.buttonSouth = false;
            amorfos::onButtonRelease(BUTTON_BOTTOM);
        } else {
            input.buttonSouth = true;
            amorfos::onButtonPress(BUTTON_BOTTOM);
        }
    } else if ((PIND << BUTTON_LEFT) == 0) {
        if (input.buttonEast) {
            input.buttonEast = false;
            amorfos::onButtonRelease(BUTTON_LEFT);
        } else {
            input.buttonEast = true;
            amorfos::onButtonPress(BUTTON_LEFT);
        }
    } else if ((PIND << BUTTON_START) == 0) {
        if (input.buttonStart) {
            input.buttonStart = false;
            amorfos::onButtonRelease(BUTTON_START);
        } else {
            input.buttonStart = true;
            amorfos::onButtonPress(BUTTON_START);
        }
    } else if ((PIND << BUTTON_SELECT) == 0) {
        if (input.buttonSelect) {
            input.buttonSelect = false;
            amorfos::onButtonRelease(BUTTON_SELECT);
        } else {
            input.buttonSelect = true;
            amorfos::onButtonPress(BUTTON_SELECT);
        }
    }
}

ISR(PCINT0_vect) {
    if ((PINB << (BUTTON_JOYSTICK - 9)) == 0) {
        if (input.buttonJoystick) {
            input.buttonJoystick = false;
            amorfos::onButtonRelease(BUTTON_JOYSTICK);
        } else {
            input.buttonJoystick = true;
            amorfos::onButtonPress(BUTTON_JOYSTICK);
        }
    }
}

void setup() {
    cli();
    // setup input
    // setup intrerrupts for buttons
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22) | (1 << PCINT23) | (1 << PCINT0);
    // setup LED output
    DDRD |= (1 << LED0);
    DDRD |= (1 << LED1);
    // lcd setup
    ucg.begin(UCG_FONT_MODE_SOLID);
    ucg.setClipRange(0, -32, 128, 128);
    ucg.setFont(ucg_font_ncenR12_tr);
    ucg.clearScreen();
    sei();
    amorfos::start();
}

void loop() {
    // update time
    float oldTime = time;
    time = millis() / 1000.0f;
    float deltaTime = time - oldTime;
    amorfos::update(deltaTime);
    amorfos_internal::render(amorfos::getEntities(), amorfos::getEntityCount(), &ucg);
    amorfos_internal::checkCollisions(amorfos::getEntities(), amorfos::getEntityCount());
    // update joystick input
    input.joystickX = analogRead(A0) / 1023.0f;
    input.joystickY = analogRead(A1) / 1023.0f;
}