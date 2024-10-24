// Source
#include "localization.h"

// Private

// Public
void localizationInit(const char *value)
{
    if (strcmp(value, "EN") == 0)
    {
        localizationCurrent = &localization_EN;
    }
    else if (strcmp(value, "IT") == 0)
    {
        localizationCurrent = &localization_IT;
    }
    else
    {
        localizationCurrent = &localization_EN;
    }
}
