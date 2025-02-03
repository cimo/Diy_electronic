#ifndef HELPER_H
#define HELPER_H

#include <stdbool.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"

bool helperMillisecondElapsed(uint32_t *previousTime, uint32_t interval);
const char *helperFloatToString(float value);
const char *helperConvertSizeUnit(uint64_t byte);

#endif
