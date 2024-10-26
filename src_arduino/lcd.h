#ifndef LCD_H
#define LCD_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

bool lcdInit(uint8_t screenWidth, uint8_t screenHeight, int8_t oledReset, int8_t screenAddres);
void lcdDraw();

#endif
