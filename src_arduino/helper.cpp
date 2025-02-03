// Source
#include <wiring_time.h>
#include "helper.h"

// Private

// Public
bool helperMillisecondElapsed(unsigned long *previousTime, unsigned long interval)
{
    unsigned long currentTime = millis();

    if (currentTime - *previousTime >= interval)
    {
        *previousTime = currentTime;

        return true;
    }

    return false;
}
