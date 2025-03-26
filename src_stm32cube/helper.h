#ifndef HELPER_H
#define HELPER_H

#include <stdbool.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"

bool helperMillisecondElapsed(uint32_t *previousTime, uint32_t interval);
bool helperI2cScan(I2C_HandleTypeDef *hi2c, uint8_t addr);
const char *helperFloatToString(float value);
const char *helperConvertSizeUnit(uint64_t byte);

#endif
