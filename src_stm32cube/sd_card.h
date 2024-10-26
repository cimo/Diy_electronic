#ifndef SD_CARD_H
#define SD_CARD_H

#include "fatfs.h"
#include "serial.h"
#include "localization.h"
#include <stdbool.h>
#include <stdio.h>

typedef void (*SdCardOpenCallback)(FIL *file);

bool sdCardInit();
void sdCardOpen(const char *filePath, int mode, SdCardOpenCallback callback);

#endif
