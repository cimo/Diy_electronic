// Source
#include "display_i2c_command.h"

// Private
const char *messageList[13] = {
    "test 1", "test 2", "test 3", "test 4", "test 5", "test 6",
    "test 7", "test 8", "test 9", "test 10", "test 11", "test 12", ""};

bool i2cScan(I2C_HandleTypeDef *hi2c, uint8_t addr)
{
    HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(hi2c, addr, 1, 20000);

    if (status == HAL_OK)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Public
void i2cLcdCommandInit(I2C_HandleTypeDef *hi2c)
{

    if (i2cScan(hi2c, 0x78))
    {
        i2cLcdClear();
        i2cLcdInit(&Font_7x10, 6, 13);
        i2cLcdText("stm32f103c8t6", 1, 0);
    }
}

void i2cLcdCommandLoop()
{
    // i2cLcdTextScrollHorizontal("test 0", 0, 1, 0);
    // i2cLcdTextScrollHorizontal("test 1", 1, 1, 1);

    // i2cLcdTextScrollVertical("test 0", 0, 1, 4);
    // i2cLcdTextScrollVertical("test 1", 1, 1, 5);

    // i2cLcdTextScrollVerticalBuffer(messageList, 1);
}
