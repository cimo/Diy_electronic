#ifndef SERIAL_COMMAND_H
#define SERIAL_COMMAND_H

#include "serial.h"

void serialCommandAsynchronousInit(UART_HandleTypeDef *huart);
void serialCommandSingleWireInit(UART_HandleTypeDef *huart);

#endif
