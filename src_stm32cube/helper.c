// Source
#include "helper.h"

// Private

// Public
bool millisecondElapsed(uint32_t *previousTime, uint32_t interval)
{
    uint32_t currentTime = HAL_GetTick();

    if (currentTime - *previousTime >= interval)
    {
        *previousTime = currentTime;

        return true;
    }

    return false;
}
