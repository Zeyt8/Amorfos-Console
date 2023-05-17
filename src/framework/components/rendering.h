#pragma once

#include "entity.h"
#include "Ucglib.h"

namespace amorfos_internal
{
    void render(amorfos::Entity** entities, int entityCount, Ucglib_ILI9163_18x128x128_SWSPI* ucg);
}

namespace amorfos
{
    #define LED0 PD0
    #define LED1 PD1

    void setLED(bool on, int led);
}