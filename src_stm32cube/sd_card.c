// Source
#include "sd_card.h"

// Private
FATFS fatFs;
FIL fil;
FRESULT fResult;
char buffer[50];

// Public
bool sdCardInit()
{
    fResult = f_mount(&fatFs, "", 0);

    fResult = f_mkfs("", 0, 0);

    if (fResult != FR_OK)
    {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%s%d", localizationCurrent->sdCardError_init, fResult);
        serialSendMessage(buffer);

        return false;
    }

    fResult = f_mount(&fatFs, "", 1);

    if (fResult != FR_OK)
    {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%s%d", localizationCurrent->sdCardError_mount, fResult);
        serialSendMessage(buffer);

        return false;
    }

    return true;
}

void sdCardOpen(char *filePath, int mode, SdCardOpenCallback callback)
{
    fResult = f_open(&fil, filePath, mode);

    if (fResult != FR_OK)
    {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%s%d", localizationCurrent->sdCardError_open, fResult);
        serialSendMessage(buffer);
    }
    else
    {
        callback(&fil);
    }

    f_close(&fil);
}
