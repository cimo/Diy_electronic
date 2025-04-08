// Source
#include "display_i2c_command.h"

// Private
const char *messageList[15] = {
    "cimo 1", "cimo 2", "cimo 3", "cimo 4", "cimo 5", "cimo 6", "cimo 7",
    "cimo 8", "cimo 9", "cimo 10", "cimo 11", "cimo 12", "cimo 13", "cimo 14", ""};

// Public
void lcdI2cCommandInit()
{
    i2cLcdInit(&SH1106_128x64, 0x3C, System5x7, 128, 64, 7, 15);
    i2cLcdClear();
    i2cLcdText("stm32f103c8t6", 0, 0);
}

void lcdI2cCommandLoop()
{
    // lcdI2cTextScrollHorizontal("cimo 0", 0, 0, 0);
    // lcdI2cTextScrollHorizontal("cimo 1", 1, 0, 1);

    // lcdI2cTextScrollVertical("cimo 0", 0, 0, 6);
    // lcdI2cTextScrollVertical("cimo 1", 1, 0, 7);

    // lcdI2cTextScrollVerticalBuffer(messageList, 0);
}
