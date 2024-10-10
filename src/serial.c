#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Source
#include "main.h"
#include "serial.h"

#define RX_BUFFER_SIZE 20

static UART_HandleTypeDef *uartHandle;

volatile bool transmissionComplete = false; // Flag to indicate completion
volatile uint8_t *transmissionBuffer;       // Pointer to the current transmission buffer
volatile uint16_t transmissionSize;         // Size of the current transmission buffer

uint8_t uartRxBuffer[RX_BUFFER_SIZE];
uint8_t rxIndex = 0;

// Private
void sendMessage(uint8_t *message, uint16_t size)
{
    transmissionBuffer = message; // Set the buffer to the message to be sent
    transmissionSize = size;      // Set the size of the message
    transmissionComplete = false; // Reset the transmission complete flag

    HAL_UART_Transmit_IT(uartHandle, (const uint8_t *)transmissionBuffer, transmissionSize);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        // Transmission complete logic, if needed
        transmissionComplete = true; // Mark that the transmission is complete

        // Check if there’s a next message to send
        if (transmissionBuffer != NULL && transmissionSize > 0)
        {
            // Start the next transmission
            HAL_UART_Transmit_IT(huart, (const uint8_t *)transmissionBuffer, transmissionSize);

            // Reset the transmission buffer and size after starting the next transmission
            transmissionBuffer = NULL;
            transmissionSize = 0;
        }
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        if (uartRxBuffer[rxIndex] == '\n' || uartRxBuffer[rxIndex] == '\r')
        {
            uartRxBuffer[rxIndex] = '\0';

            sendMessage((uint8_t *)"Received: ", 10);
            sendMessage(uartRxBuffer, rxIndex);
            sendMessage((uint8_t *)"\r\n", 2);

            for (int i = 0; i < rxIndex; i++)
            {
                uartRxBuffer[i] = tolower(uartRxBuffer[i]);
            }

            if (strcmp((char *)uartRxBuffer, "e_fan_on") == 0)
            {
                HAL_GPIO_WritePin(E_FAN_GPIO_Port, E_FAN_Pin, GPIO_PIN_SET);

                sendMessage((uint8_t *)"E_FAN: on.\r\n", 12);
            }
            else if (strcmp((char *)uartRxBuffer, "e_fan_off") == 0)
            {
                HAL_GPIO_WritePin(E_FAN_GPIO_Port, E_FAN_Pin, GPIO_PIN_RESET);

                sendMessage((uint8_t *)"E_FAN: off.\r\n", 13);
            }
            else
            {
                sendMessage((uint8_t *)"Unknown command.\r\n", 18);
            }

            rxIndex = 0;
        }
        else
        {
            rxIndex++;

            if (rxIndex >= RX_BUFFER_SIZE)
            {
                rxIndex = 0;
            }
        }

        HAL_StatusTypeDef result = HAL_UART_Receive_IT(uartHandle, &uartRxBuffer[rxIndex], 1);

        if (result != HAL_OK)
        {
            if (result == HAL_ERROR)
            {
                sendMessage((uint8_t *)"UART Error: General failure.\r\n", 32);
            }
            else if (result == HAL_BUSY)
            {
                sendMessage((uint8_t *)"UART Busy: Cannot receive now.\r\n", 34);
            }

            HAL_UART_Receive_IT(uartHandle, &uartRxBuffer[rxIndex], 1);
        }
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        HAL_UART_Receive_IT(uartHandle, uartRxBuffer, RX_BUFFER_SIZE);
    }
}

// Public
void SerialInit(UART_HandleTypeDef *huart)
{
    uartHandle = huart;

    HAL_UART_Receive_IT(uartHandle, &uartRxBuffer[rxIndex], 1);
}
