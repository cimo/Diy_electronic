#ifndef SD_SPI_H
#define SD_SPI_H

#include <SdFat.h>

typedef void (*SdCardOpenCallback)(FsFile &fsFile);

bool sdCardInit(int pinNumber);
void sdCardOpen(char *filePath, int mode, SdCardOpenCallback callback);
void sdCardList(char *path);
void sdCardFormat();

#endif
