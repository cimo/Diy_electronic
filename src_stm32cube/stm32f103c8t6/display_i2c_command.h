#ifndef DISPLAY_I2C_COMMAND_H
#define DISPLAY_I2C_COMMAND_H

#include "serial.h"
#include "display_i2c.h"

void i2cLcdCommandInit(I2C_HandleTypeDef *hi2c);
void i2cLcdCommandLoop();

#endif
