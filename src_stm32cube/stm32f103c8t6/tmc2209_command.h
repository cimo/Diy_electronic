#ifndef TMC2209_COMMAND_H
#define TMC2209_COMMAND_H

#include "tmc2209.h"

void tmc2209CommandInit(UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim);
void tmc2209CommandLoop();

#endif
