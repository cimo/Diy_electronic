// Source
#include "i2c_lcd.h"

// Private
SSD1306AsciiWire display;

// Public
void i2cLcdInit(const DevType *driver, const int8_t address, const uint8_t *font)
{
    Wire.begin();
    Wire.setClock(400000L);

    display.begin(driver, address);
    display.setFont(font);
}

void i2cLcdText(const char *text)
{
    display.clear();
    display.println(text);
}

void i2cLcdTextScrollHorizontal(const char *text, int speed)
{
    //...
}

void i2cLcdTextScrollVertical(const char *textList[], int speed)
{
    //...
}
