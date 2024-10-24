// Source
#include "lcd.h"

// Private

// Public
void lcdInit()
{
    SSD1306_Init();
}

void lcdDraw()
{
    SSD1306_GotoXY(0, 0);
    SSD1306_Puts("CIMO", &Font_11x18, 1);
    SSD1306_UpdateScreen();
}
