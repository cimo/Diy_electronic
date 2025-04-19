#ifndef SERIAL_H
#define SERIAL_H

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "main.h"
#include "localization.h"

#define SERIAL_BUFFER_SIZE 255

typedef void (*SerialRxCallbackAsynchronous)();
typedef void (*SerialRxCallbackSingleWire)();

void serialAsynchronousInit(UART_HandleTypeDef *huart, SerialRxCallbackAsynchronous rxCallback);
void serialAsynchronousSendMessage(const char *format, ...);
bool serialAsynchronousReceiveMessageCheck(const char *message);

void serialSingleWireInit(UART_HandleTypeDef *huart, SerialRxCallbackSingleWire rxCallback);
void serialSingleWireSendMessage(const char *format, ...);
bool serialSingleWireReceiveMessageCheck(const char *message);

#endif
