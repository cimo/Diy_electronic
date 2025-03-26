#ifndef DISPLAY_I2C_COMMAND_H
#define DISPLAY_I2C_COMMAND_H

#include "helper.h"
#include "serial.h"
#include "display_i2c.h"

void lcdI2cCommandInit(I2C_HandleTypeDef *hi2c);
void lcdI2cCommandLoop();

#endif
