// Source
#include "lcd.h"

// Private
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Public
bool lcdInit()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
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
    display.println("Hello, World!");

    display.display();
}
