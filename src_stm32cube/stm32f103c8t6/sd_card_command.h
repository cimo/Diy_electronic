#ifndef SD_CARD_COMMAND_H
#define SD_CARD_COMMAND_H

#include "fatfs.h"
#include "serial.h"
#include "sd_card.h"

void sdCardCommandInit();
void sdCardCommandLoop();

#endif
