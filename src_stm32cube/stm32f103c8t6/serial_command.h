#ifndef SERIAL_COMMAND_H
#define SERIAL_COMMAND_H

#include "main.h"
#include "localization.h"
#include "serial.h"

void serialCommandInit(UART_HandleTypeDef *huart);
void serialCommandLoop();

#endif
