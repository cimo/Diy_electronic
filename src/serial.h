#ifndef SERIAL_H
#define SERIAL_H

#include <stdbool.h>
#include "main.h"

typedef void (*SerialCustomRxCallback)();

void SerialInit(UART_HandleTypeDef *huart, SerialCustomRxCallback callback);
bool SerialCheckCommand(const char *message);
void SerialSendMessage(const char *message);

#endif
