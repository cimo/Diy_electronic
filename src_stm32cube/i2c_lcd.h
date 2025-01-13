#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <stdbool.h>
#include "fonts.h"
#include "ssd1306.h"

void i2cLcdInit(FontDef_t *fontValue, int16_t lineTotalValue, int16_t bufferTotalValue);
void i2cLcdClear();
void i2cLcdText(char *text, uint16_t column, uint16_t row);
void i2cLcdTextScrollHorizontal(char *text, int index, uint16_t column, uint16_t row);
void i2cLcdTextScrollVertical(char *text, int index, uint16_t column, uint16_t row);
void i2cLcdTextScrollVerticalBuffer(char *messageList[], uint16_t column);

#endif
