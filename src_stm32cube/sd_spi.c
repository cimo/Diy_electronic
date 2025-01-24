// Source
#include "sd_spi.h"

// Private
FATFS fatFs;
FIL fil;
FRESULT fResult;
char buffer[50];

FATFS *pfs;
DWORD fre_clust;
uint32_t total, free_space;

// Public
bool sdCardInit()
{
    fResult = f_mount(&fatFs, "", 0);

    if (fResult != FR_OK)
    {
        snprintf(buffer, sizeof(buffer), "%s%d", localizationCurrent->sdCardError_mount, fResult);
        serialSendMessage(buffer);

        return false;
    }

    return true;
}

void sdCardSpace()
{
    f_getfree("", &fre_clust, &pfs);

    total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
    snprintf(buffer, sizeof(buffer), "%s%lu", "SD CARD Total Size: ", total);
    serialSendMessage(buffer);

    free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);
    snprintf(buffer, sizeof(buffer), "%s%lu", "SD CARD Free Space: ", free_space);
    serialSendMessage(buffer);
}

void sdCardOpen(const char *filePath, uint8_t mode, SdCardOpenCallback callback)
{
    fResult = f_open(&fil, filePath, mode);

    if (fResult != FR_OK)
    {
        snprintf(buffer, sizeof(buffer), "%s%d", localizationCurrent->sdCardError_open, fResult);
        serialSendMessage(buffer);

        fResult = f_close(&fil);
    }
    else
    {
        callback(&fil);
    }
}

void sdCardPut(const char *data)
{
    fResult = f_puts(data, &fil);

    if (fResult != FR_OK)
    {
        // snprintf(buffer, sizeof(buffer), "%s%d", localizationCurrent->sdCardError_put, fResult);
        // serialSendMessage(buffer);
    }

    fResult = f_close(&fil);

    snprintf(buffer, sizeof(buffer), "%s", "SD CARD write ok.");
    serialSendMessage(buffer);
}
