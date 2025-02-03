#ifndef DISPLAY_I2C_H
#define DISPLAY_I2C_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f1xx_hal.h"
#include "ssd1306.h"
#include "font.h"

void i2cLcdInit(FontDef_t *fontValue, uint16_t lineTotalValue, uint16_t bufferTotalValue);
void i2cLcdClear();
void i2cLcdText(const char *text, uint16_t column, uint16_t row);
void i2cLcdTextScrollHorizontal(const char *text, uint8_t index, uint16_t column, uint16_t row);
void i2cLcdTextScrollVertical(const char *text, uint8_t index, uint16_t column, uint16_t row);
void i2cLcdTextScrollVerticalBuffer(const char *messageList[], uint16_t column);

#endif
