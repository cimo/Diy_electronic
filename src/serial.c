#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// Source
#include "serial.h"

static UART_HandleTypeDef *uartHandle = NULL;
static SerialCustomRxCallback customRxCallback = NULL;

#define BUFFER_SIZE 50
uint8_t rxBuffer[BUFFER_SIZE];
uint8_t rxIndex = 0;

/*const uint8_t *txMessage = NULL;
uint16_t txSize = 0;
bool isTxComplete = false;*/

#define TX_QUEUE_SIZE 5

typedef struct
{
    char messageList[TX_QUEUE_SIZE][BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} TxQueue;

TxQueue txQueue = {.messageList = {{0}}, .head = 0, .tail = 0, .count = 0};

// Private
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandle->Instance)
    {
        if (rxBuffer[rxIndex] == '\n')
        {
            rxBuffer[rxIndex] = '\0';

            if (customRxCallback != NULL)
            {
                customRxCallback();
            }

            rxIndex = 0;
        }
        else
        {
            if (rxIndex < BUFFER_SIZE - 1)
            {
                rxIndex++;
            }
            else
            {
                SerialSendMessage("UART error: Buffer overflow.");

                rxIndex = 0;
            }
        }

        HAL_UART_Receive_IT(uartHandle, &rxBuffer[rxIndex], 1);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandle->Instance)
    {
        /*txMessage = NULL;
        txSize = 0;
        isTxComplete = true;*/

        txQueue.head = (txQueue.head + 1) % TX_QUEUE_SIZE;
        txQueue.count--;

        if (txQueue.count > 0)
        {
            HAL_UART_Transmit_IT(uartHandle, (const uint8_t *)txQueue.messageList[txQueue.head], strlen(txQueue.messageList[txQueue.head]));
        }
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandle->Instance)
    {
        SerialSendMessage("UART error: General failure.");

        rxIndex = 0;

        HAL_UART_Receive_IT(uartHandle, &rxBuffer[rxIndex], 1);
    }
}

// Public
void SerialInit(UART_HandleTypeDef *huart, SerialCustomRxCallback rxCallback)
{
    uartHandle = huart;
    customRxCallback = rxCallback;

    HAL_UART_Receive_IT(uartHandle, &rxBuffer[rxIndex], 1);
}

bool SerialCheckCommand(const char *message)
{
    if (strcmp((char *)rxBuffer, message) == 0)
    {
        return true;
    }

    return false;
}

void SerialSendMessage(const char *message)
{
    /*char messageFormatted[BUFFER_SIZE];
    snprintf(messageFormatted, sizeof(messageFormatted), "%s\r\n", message);

    txMessage = (const uint8_t *)messageFormatted;
    txSize = (uint16_t)strlen(messageFormatted);
    isTxComplete = false;

    HAL_UART_Transmit_IT(uartHandle, txMessage, txSize);*/

    if (txQueue.count < TX_QUEUE_SIZE)
    {
        snprintf(txQueue.messageList[txQueue.tail], sizeof(txQueue.messageList[txQueue.tail]), "%s\r\n", message);

        txQueue.tail = (txQueue.tail + 1) % TX_QUEUE_SIZE;
        txQueue.count++;

        if (txQueue.count == 1)
        {
            HAL_UART_Transmit_IT(uartHandle, (const uint8_t *)txQueue.messageList[txQueue.head], strlen(txQueue.messageList[txQueue.head]));
        }
    }
}
