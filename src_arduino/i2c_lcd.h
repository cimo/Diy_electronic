#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>

static int16_t I2C_LCD_WIDTH = 0;
static int16_t I2C_LCD_HEIGHT = 0;

void i2cLcdInit(const DevType *driver, const int8_t address, const uint8_t *font, int16_t width, int16_t height, int16_t lineTotalValue, int16_t bufferTotalValue);
void i2cLcdClear();
void i2cLcdText(const char *text, uint8_t column, uint8_t row);
void i2cLcdTextScrollHorizontal(const char *text, int index, uint8_t column, uint8_t row);
void i2cLcdTextScrollVertical(const char *text, int index, uint8_t column, uint8_t row);
void i2cLcdTextScrollVerticalBuffer(const char *messages[], uint8_t column);

#endif
