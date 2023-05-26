#pragma once

#include "entity.h"
#include "Ucglib.h"

namespace amorfos_internal
{
    void render(amorfos::Entity** entities, int entityCount, Ucglib_ILI9341_18x240x320_HWSPI* ucg);
}

namespace amorfos
{
    #define LCD_WIDTH 240
    #define LCD_HEIGHT 320
    #define LED0 PD1
    #define LED1 PD0                                                                 

    /// @brief Sets the state of an LED
    /// @param on The state of the LED
    /// @param led The LED to set. Use LED0 or LED1
    void setLED(bool on, int led);
}