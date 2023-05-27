#include "Arduino.h"
#include <stdbool.h>
#include <SPI.h>
#include "Ucglib.h"

#include "src/framework/amorfos.h"

Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 12);

volatile amorfos::Input input;
float time = 0;
volatile int debouncing = 0;

ISR(PCINT2_vect) {
    if (millis() - debouncing < 100) return;
    debouncing = millis();
    if ((PIND & (1 << BUTTON_TOP)) == 0) {
        if (input.buttonNorth) {
            input.buttonNorth = false;
            amorfos::onButtonRelease(BUTTON_TOP);
        } else {
            input.buttonNorth = true;
            amorfos::onButtonPress(BUTTON_TOP);
        }
    } else if ((PIND & (1 << BUTTON_RIGHT)) == 0) {
        if (input.buttonWest) {
            input.buttonWest = false;
            amorfos::onButtonRelease(BUTTON_RIGHT);
        } else {
            input.buttonWest = true;
            amorfos::onButtonPress(BUTTON_RIGHT);
        }
    } else if ((PIND & (1 << BUTTON_BOTTOM)) == 0) {
        if (input.buttonSouth) {
            input.buttonSouth = false;
            amorfos::onButtonRelease(BUTTON_BOTTOM);
        } else {
            input.buttonSouth = true;
            amorfos::onButtonPress(BUTTON_BOTTOM);
        }
    } else if ((PIND & (1 << BUTTON_LEFT)) == 0) {
        if (input.buttonEast) {
            input.buttonEast = false;
            amorfos::onButtonRelease(BUTTON_LEFT);
        } else {
            input.buttonEast = true;
            amorfos::onButtonPress(BUTTON_LEFT);
        }
    }/* else if ((PIND & (1 << BUTTON_START)) == 0) {
        if (input.buttonStart) {
            input.buttonStart = false;
            amorfos::onButtonRelease(BUTTON_START);
        } else {
            input.buttonStart = true;
            amorfos::onButtonPress(BUTTON_START);
        }
    } else if ((PIND & (1 << BUTTON_SELECT)) == 0) {
        if (input.buttonSelect) {
            input.buttonSelect = false;
            amorfos::onButtonRelease(BUTTON_SELECT);
        } else {
            input.buttonSelect = true;
            amorfos::onButtonPress(BUTTON_SELECT);
        }
    }*/
}

ISR(PCINT0_vect) {
    if (millis() - debouncing < 100) return;
    debouncing = millis();
    if ((PINB & (1 << (BUTTON_JOYSTICK - 8))) == 0) {
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
    amorfos::start();
}

void loop() {
    // update time
    float oldTime = time;
    time = millis() / 1000.0f;
    float deltaTime = time - oldTime;
    amorfos::update(deltaTime);
    amorfos_internal::render(amorfos::entities, amorfos::entityCount, &ucg);
    amorfos_internal::checkCollisions(amorfos::entities, amorfos::entityCount);
    // destroy required objects
    for (int i = amorfos::entityCount - 1; i >= 0; i--) {
        if (amorfos::entities[i]->isDestroyed) {
            amorfos::entities[i] = amorfos::entities[amorfos::entityCount - 1];
            amorfos::entityCount--;
            free(amorfos::entities[amorfos::entityCount]);
        }
    }
    amorfos::entities = (amorfos::Entity**)realloc(amorfos::entities, sizeof(amorfos::Entity*) * amorfos::entityCount);
    // update joystick input
    input.joystickX = (1023.0 - analogRead(A4)) / 1023.0;
    input.joystickY = (1023.0 - analogRead(A5)) / 1023.0;
}