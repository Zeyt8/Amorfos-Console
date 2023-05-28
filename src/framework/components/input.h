#pragma once

namespace amorfos
{
    #define BUTTON_TOP 2
    #define BUTTON_RIGHT 3
    #define BUTTON_BOTTOM 4
    #define BUTTON_LEFT 5
    #define BUTTON_JOYSTICK 6

    typedef struct Input {
        float joystickX;
        float joystickY;
        bool buttonNorth;
        bool buttonWest;
        bool buttonSouth;
        bool buttonEast;
        bool buttonJoystick;
    } Input;

    volatile inline Input input;

    /// @brief Called when a button is pressed
    /// @param button Id of the button. Use the BUTTON_* constants
    extern void onButtonPress(int button);
    /// @brief Called when a button is released
    /// @param button Id of the button. Use the BUTTON_* constants
    extern void onButtonRelease(int button);
}