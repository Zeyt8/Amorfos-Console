#pragma once

namespace amorfos
{
    #define BUTTON_NORTH 2
    #define BUTTON_WEST 3
    #define BUTTON_SOUTH 4
    #define BUTTON_EAST 5
    #define BUTTON_START 6
    #define BUTTON_SELECT 7
    #define BUTTON_JOYSTICK 8

    typedef struct Input {
        float joystickX;
        float joystickY;
        bool buttonNorth;
        bool buttonWest;
        bool buttonSouth;
        bool buttonEast;
        bool buttonStart;
        bool buttonSelect;
        bool buttonJoystick;
    } Input;

    /// @brief Called when a button is pressed
    /// @param button Id of the button. Use the BUTTON_* constants
    extern void onButtonPress(int button);
    /// @brief Called when a button is released
    /// @param button Id of the button. Use the BUTTON_* constants
    extern void onButtonRelease(int button);
}