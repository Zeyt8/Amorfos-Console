#pragma once

#define BUTTON_NORTH 0
#define BUTTON_SOUTH 1
#define BUTTON_EAST 2
#define BUTTON_WEST 3

typedef struct Input {
    float joystickX;
    float joystickY;
    bool buttonNorth;
    bool buttonSouth;
    bool buttonEast;
    bool buttonWest;
} Input;

/// @brief Called when a button is pressed
/// @param button Id of the button. Use the BUTTON_* constants
void OnButtonPress(int button);
/// @brief Called when a button is released
/// @param button Id of the button. Use the BUTTON_* constants
void OnButtonRelease(int button);