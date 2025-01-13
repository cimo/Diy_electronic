#ifndef SD_CARD_H
#define SD_CARD_H

#include <stdbool.h>
#include <stdio.h>
#include "fatfs.h"
#include "localization.h"
#include "serial.h"

typedef void (*SdCardOpenCallback)(FIL *file);

bool sdCardInit();
void sdCardOpen(char *filePath, int mode, SdCardOpenCallback callback);
void sdCardList(char *path);
void sdCardFormat();

#endif
