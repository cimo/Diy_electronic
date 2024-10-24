#ifndef SD_CARD_H
#define SD_CARD_H

#include <SdFat.h>

typedef void (*Callback)(FsFile &file);

const int SD_CS_PIN = PA15;

bool sdCardInit();
void sdCardOpen(const char *filePath, int mode, Callback callback);
void sdCardList(const char *path);
void sdCardFormat();

#endif
