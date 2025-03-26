// Source
#include "display_i2c_command.h"

// Private
const char *messageList[13] = {
    "test 1", "test 2", "test 3", "test 4", "test 5", "test 6",
    "test 7", "test 8", "test 9", "test 10", "test 11", "test 12", ""};

// Public
void lcdI2cCommandInit(I2C_HandleTypeDef *hi2c)
{

    if (helperI2cScan(hi2c, 0x78))
    {
        i2cLcdClear();
        i2cLcdInit(&Font_7x10, 6, 13);
        i2cLcdText("stm32f103c8t6", 1, 0);
    }
}

void lcdI2cCommandLoop()
{
    // i2cLcdTextScrollHorizontal("test 0", 0, 1, 0);
    // i2cLcdTextScrollHorizontal("test 1", 1, 1, 1);

    // i2cLcdTextScrollVertical("test 0", 0, 1, 4);
    // i2cLcdTextScrollVertical("test 1", 1, 1, 5);

    // i2cLcdTextScrollVerticalBuffer(messageList, 1);
}
