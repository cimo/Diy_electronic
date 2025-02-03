#ifndef SERIAL_H
#define SERIAL_H

#define SERIAL_BUFFER_SIZE 255
#define TX_QUEUE_SIZE 20

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "localization.h"

typedef void (*SerialCustomRxCallback)();

void serialInit(UART_HandleTypeDef *huart, SerialCustomRxCallback callback);
void serialSendMessage(const char *message);
bool serialCheckCommand(const char *message);

#endif
