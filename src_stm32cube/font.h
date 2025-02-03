#ifndef FONT_H
#define FONT_H

#include <string.h>
#include "stm32f1xx_hal.h"

typedef struct
{
    uint8_t FontWidth;
    uint8_t FontHeight;
    const uint16_t *data;
} FontDef_t;

typedef struct
{
    uint16_t Length;
    uint16_t Height;
} FONTS_SIZE_t;

extern FontDef_t Font_7x10;

const char *fontStringSize(const char *text, FONTS_SIZE_t *sizeStruct, FontDef_t *font);

#endif
