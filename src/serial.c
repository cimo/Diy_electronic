#include <string.h>

// Source
#include "serial.h"

#define BUFFER_SIZE 256

static UART_HandleTypeDef *uartHandle;
static volatile uint8_t rxIndex = 0;
static char bufferRx[BUFFER_SIZE];

void USART3_IRQHandler(void)
{
    if (__HAL_UART_GET_FLAG(uartHandle, UART_FLAG_RXNE))
    {
        char receivedChar;
        HAL_UART_Receive_IT(uartHandle, (uint8_t *)&receivedChar, 1); // Receive one byte

        // Store in buffer if there is space
        if (rxIndex < BUFFER_SIZE - 1)
        {
            bufferRx[rxIndex++] = receivedChar; // Store the received character
            if (receivedChar == '\n')
            {                             // End of message detected
                bufferRx[rxIndex] = '\0'; // Null-terminate the string
                SerialSend(bufferRx);     // Send response back
                rxIndex = 0;              // Reset index for the next message
            }
        }
    }
}

void SerialInit(UART_HandleTypeDef *huart)
{
    uartHandle = huart;
    HAL_UART_Receive_IT(uartHandle, (uint8_t *)&bufferRx[0], 1);
}

void SerialSend(const char *data)
{
    HAL_UART_Transmit_IT(uartHandle, (uint8_t *)data, strlen(data));
}
