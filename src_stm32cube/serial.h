#ifndef SERIAL_H
#define SERIAL_H

#include <stdbool.h>
#include "stm32f1xx_hal.h"

typedef void (*SerialCustomRxCallback)();

void serialInit(UART_HandleTypeDef *huart, SerialCustomRxCallback callback);
void serialSendMessage(const char *message);
bool serialCheckCommand(const char *message);

#endif
