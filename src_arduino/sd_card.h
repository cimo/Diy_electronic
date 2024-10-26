#ifndef SD_CARD_H
#define SD_CARD_H

#include <SdFat.h>

typedef void (*SdCardOpenCallback)(FsFile &fsFile);

bool sdCardInit(int pinNumber);
void sdCardOpen(const char *filePath, int mode, SdCardOpenCallback callback);
void sdCardList(const char *path);
void sdCardFormat();

#endif
