#ifndef HELPER_H
#define HELPER_H

#include <stdbool.h>
#include "stm32f1xx_hal.h"

bool millisecondElapsed(uint32_t *previousTime, uint32_t interval);

#endif
