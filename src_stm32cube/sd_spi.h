#ifndef SD_SPI_H
#define SD_SPI_H

#include <stdbool.h>
#include "ff.h"
#include "helper.h"
#include "serial.h"
#include "localization.h"

typedef void (*sdSpiCallback)();

bool sdSpiMount();
void sdSpiSpace();
void sdSpiDirectoryList(const char *path, bool isShowHidden);
void sdSpiWrite(const char *filePath, const char *data, bool isAppend, sdSpiCallback callback);
void sdSpiRead(const char *filePath, sdSpiCallback callback);
void sdSpiDelete(const char *filePath, sdSpiCallback callback);
bool sdSpiUnmount();

#endif
