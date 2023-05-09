#pragma once

#include "arduino.h"
#include "input.h"
#include "entity.h"
#include "rendering.h"
#include "audio.h"
#include "vector.h"

Entity** entities;
unsigned int entityCount;
Input input;
float time;

/// @brief Called at the start of the game
void Start();
/// @brief The main game loop. Delta time is the time since the last frame
/// @param deltaTime 
void Update(float deltaTime);
/// @brief Create an entity
/// @return The created entity
Entity* CreateEntity() {
    Entity* entity = new Entity();
    entity->type = 0;
    entity->position = Vector3(0, 0, 0);
    entity->children = NULL;
    entity->childCount = 0;
    entity->parent = NULL;
    entity->color = Vector3(1, 1, 1);
    entity->isVisible = true;
    return entity;
}
/// @brief Destroy an entity
void DestroyEntity() {
    for (int i = 0; i < entityCount; i++) {
        if (entities[i] == entity) {
            entities[i] = entities[entityCount - 1];
            entityCount--;
            break;
        }
    }
}

// button north
ISR(PCINT18_vect) {
    if (input.buttonNorth) {
        input.buttonNorth = false;
        OnButtonRelease(BUTTON_NORTH);
    } else {
        input.buttonNorth = true;
        OnButtonPress(BUTTON_NORTH);
    }
}

// button east
ISR(PCINT19_vect) {
    if (input.buttonEast) {
        input.buttonEast = false;
        OnButtonRelease(BUTTON_EAST);
    } else {
        input.buttonEast = true;
        OnButtonPress(BUTTON_EAST);
    }
}

// button south
ISR(PCINT20_vect) {
    if (input.buttonSouth) {
        input.buttonSouth = false;
        OnButtonRelease(BUTTON_SOUTH);
    } else {
        input.buttonSouth = true;
        OnButtonPress(BUTTON_SOUTH);
    }
}

// button east
ISR(PCINT21_vect) {
    if (input.buttonWest) {
        input.buttonWest = false;
        OnButtonRelease(BUTTON_WEST);
    } else {
        input.buttonWest = true;
        OnButtonPress(BUTTON_WEST);
    }
}

// button joystick
ISR(PCINT22_vect) {
    if (input.buttonJoystick) {
        input.buttonJoystick = false;
        OnButtonRelease(BUTTON_JOYSTICK);
    } else {
        input.buttonJoystick = true;
        OnButtonPress(BUTTON_JOYSTICK);
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
    Start();
}

void loop() {
    // update time
    float oldTime = time;
    time = millis() / 1000.0f;
    float deltaTime = time - oldTime;
    Update(deltaTime);
    render(entities, entityCount);
    // update joystick input
    input.joystickY = PIND & (1 << PD0) / 1023.0f;
    input.joystickX = PIND & (1 << PD1) / 1023.0f;
}