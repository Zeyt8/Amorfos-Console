#pragma once

#include "entity.h"
#include "../thirdparty/TFT_ILI9163C/TFT_ILI9163C.h"

namespace amorfos_internal
{
    void render(amorfos::Entity** entities, int entityCount, TFT_ILI9163C* tft);
}