#pragma once

#include "input.h"
#include "entity.h"
#include "vector.h"

Input input;

void Start();
void Update(float deltaTime);

void setup() {
    Start();
}

void loop() {
    Update(0.1f);
}