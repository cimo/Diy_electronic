// Source
#include "lcd.h"

// Private
Adafruit_SSD1306 display;

// Public
bool lcdInit(uint8_t screenWidth, uint8_t screenHeight, int8_t oledReset, int8_t screenAddres)
{
    display = Adafruit_SSD1306(screenWidth, screenHeight, &Wire, oledReset);

    if (!display.begin(SSD1306_SWITCHCAPVCC, screenAddres))
    {
        Serial.println("lcd.cpp - Error: lcdInit()");

        return false;
    }

    return true;
}

void lcdDraw()
{
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("CIMO");

    display.display();
}
