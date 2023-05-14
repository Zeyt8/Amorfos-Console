#pragma once

#include "entity.h"
#include "../thirdparty/TFT_ILI9163C/TFT_ILI9163C.h"

namespace amorfos_internal
{
    void render(amorfos::Entity** entities, int entityCount, TFT_ILI9163C* tft);
}

namespace amorfos
{
    #define LED0 PD0
    #define LED1 PD1

    void setLED(bool on, int led);
}