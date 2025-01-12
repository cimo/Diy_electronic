#ifndef SERIAL_H
#define SERIAL_H

#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "localization.h"

typedef void (*SerialCustomRxCallback)();

void serialInit(UART_HandleTypeDef *huart, SerialCustomRxCallback callback);
void serialSendMessage(const char *message);
bool serialCheckCommand(const char *message);

#endif
