// Source
#include "i2c_lcd_command.h"

// Private
char *messageList[13] = {
    "cimo 1", "cimo 2", "cimo 3", "cimo 4", "cimo 5", "cimo 6",
    "cimo 7", "cimo 8", "cimo 9", "cimo 10", "cimo 11", "cimo 12", ""};

// Public
void i2cLcdCommandInit()
{
    i2cLcdInit(&Font_7x10, 6, 13);
    i2cLcdText("stm32f103c8t6", 1, 0);
    // i2cLcdClear();
}

void i2cLcdCommandLoop()
{
    // i2cLcdTextScrollHorizontal("cimo 0", 0, 1, 0);
    // i2cLcdTextScrollHorizontal("cimo 1", 1, 1, 1);

    // i2cLcdTextScrollVertical("cimo 0", 0, 1, 4);
    // i2cLcdTextScrollVertical("cimo 1", 1, 1, 5);

    // i2cLcdTextScrollVerticalBuffer(messageList, 1);
}
