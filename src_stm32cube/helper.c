// Source
#include "helper.h"

// Private

// Public
bool helperMillisecondElapsed(uint32_t *previousTime, uint32_t interval)
{
    uint32_t currentTime = HAL_GetTick();

    if (currentTime - *previousTime >= interval)
    {
        *previousTime = currentTime;

        return true;
    }

    return false;
}

const char *helperFloatToString(float value)
{
    static char buffer[10];

    int left = (int)value;
    int right = (int)((value - left) * 100 + 0.5f);

    snprintf(buffer, sizeof(buffer), "%d.%02d", left, right);

    return buffer;
}

const char *helperConvertSizeUnit(uint64_t byte)
{
    static char buffer[12];

    double size = (double)byte;
    const char *unitList[] = {"B", "KB", "MB", "GB", "TB"};
    int index = 0;

    while (size >= 1024.0 && index < 4)
    {
        size /= 1024.0;
        index++;
    }

    snprintf(buffer, sizeof(buffer), "%s %s", helperFloatToString(size), unitList[index]);

    return buffer;
}
