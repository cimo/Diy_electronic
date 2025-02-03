#ifndef SD_SPI_H
#define SD_SPI_H

#include <stdbool.h>
#include "ff.h"
#include "helper.h"
#include "localization.h"
#include "serial.h"

typedef void (*sdSpiCallback)();

bool sdSpiMount();
void sdSpiSpace();
void sdSpiWrite(const char *filePath, uint8_t mode, const char *data, sdSpiCallback callback);
void sdSpiRead(const char *filePath, sdSpiCallback callback);
void sdSpiFileList(const char *path, bool isShowHidden);
void sdSpiDelete(const char *filePath, sdSpiCallback callback);
bool sdSpiUnmount();

#endif
