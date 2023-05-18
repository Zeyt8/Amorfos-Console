#pragma once

namespace amorfos
{
    #define BUZZER 7

    /// @brief Plays a sound on the buzzer
    /// @param frequency The frequency of the sound
    /// @param duration The duration of the sound
    void playSound(unsigned int frequency, unsigned long duration);
}