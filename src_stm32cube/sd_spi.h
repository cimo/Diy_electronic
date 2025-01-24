#ifndef SD_SPI_H
#define SD_SPI_H

#include <stdbool.h>
#include <stdio.h>
#include "fatfs.h"
#include "localization.h"
#include "serial.h"

typedef void (*SdCardOpenCallback)(FIL *fil);

bool sdCardInit();
void sdCardSpace();
void sdCardOpen(const char *filePath, uint8_t mode, SdCardOpenCallback callback);
void sdCardPut(const char *data);

#endif
