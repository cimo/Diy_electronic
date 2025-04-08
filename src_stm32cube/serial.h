#ifndef SERIAL_H
#define SERIAL_H

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "stm32f1xx_hal.h"
#include "localization.h"

#define SERIAL_BUFFER_SIZE 255

typedef void (*SerialCustomRxCallback)();

void serialInit(UART_HandleTypeDef *huart, SerialCustomRxCallback callback);
void serialSendMessage(const char *format, ...);
bool serialReceiveMessageCheck(const char *message);

#endif
