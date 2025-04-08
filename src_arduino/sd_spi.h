#ifndef SD_SPI_H
#define SD_SPI_H

#include <SPI.h>
#include <SdFat.h>

typedef void (*SdCardOpenCallback)(FsFile &fsFile);

bool sdCardInit(int pinNumber);
void sdCardOpen(const char *filePath, int mode, SdCardOpenCallback callback);
void sdCardList(const char *path);
void sdCardFormat();

#endif
