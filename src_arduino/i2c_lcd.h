#ifndef LCD_H
#define LCD_H

#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>

const int16_t I2C_LCD_WIDTH = 128;
const int16_t I2C_LCD_HEIGHT = 64;

void i2cLcdInit(const DevType *driver, const int8_t screenAddres, const uint8_t *font);

void i2cLcdText(const char *text);
void i2cLcdTextScrollHorizontal(const char *text, int speed);
void i2cLcdTextScrollVertical(const char *textList[], int speed);

#endif
