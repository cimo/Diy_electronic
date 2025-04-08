// Source
#include <wiring_time.h>
#include "helper.h"

// Private

// Public
bool helperMillisecondElapsed(uint32_t *previousTime, uint32_t interval)
{
    uint32_t currentTime = millis();

    if (currentTime - *previousTime >= interval)
    {
        *previousTime = currentTime;

        return true;
    }

    return false;
}

bool helperMicrosecondElapsed(uint32_t *previousTime, uint32_t interval)
{
    if (micros() - *previousTime >= interval)
    {
        *previousTime = micros();

        return true;
    }

    return false;
}
