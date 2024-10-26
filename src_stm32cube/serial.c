// Source
#include "serial.h"

// Private
#define TX_QUEUE_SIZE 2
#define BUFFER_SIZE 50

static UART_HandleTypeDef *uartHandle = NULL;
static SerialCustomRxCallback customRxCallback = NULL;

uint8_t rxBuffer[BUFFER_SIZE];
uint8_t rxIndex = 0;

typedef struct
{
    char messageList[TX_QUEUE_SIZE][BUFFER_SIZE];
    uint8_t start;
    uint8_t end;
    uint8_t count;
} TxQueue;

TxQueue txQueue = {.messageList = {{0}}, .start = 0, .end = 0, .count = 0};

void rxBufferReset()
{
    memset(rxBuffer, 0, sizeof(rxBuffer));
    rxIndex = 0;
}

void txQueueReset()
{
    memset(txQueue.messageList, 0, sizeof(txQueue.messageList));
    txQueue.start = 0;
    txQueue.end = 0;
}

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

            rxBufferReset();
        }
        else
        {
            if (rxIndex < BUFFER_SIZE - 1)
            {
                rxIndex++;
            }
            else
            {
                rxBufferReset();

                serialSendMessage(localizationCurrent->uartError_bufferOverflow);
            }
        }

        HAL_UART_Receive_IT(uartHandle, &rxBuffer[rxIndex], 1);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandle->Instance)
    {
        txQueue.start = (txQueue.start + 1) % TX_QUEUE_SIZE;
        txQueue.count--;

        if (txQueue.count == 0)
        {
            txQueueReset();
        }
        else if (txQueue.count > 0)
        {
            HAL_UART_Transmit_IT(uartHandle, (const uint8_t *)txQueue.messageList[txQueue.start], strlen(txQueue.messageList[txQueue.start]));
        }
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandle->Instance)
    {
        rxBufferReset();

        txQueueReset();

        serialSendMessage(localizationCurrent->uartError_generalFailure);

        HAL_UART_Receive_IT(uartHandle, &rxBuffer[rxIndex], 1);
    }
}

// Public
void serialInit(UART_HandleTypeDef *huart, SerialCustomRxCallback rxCallback)
{
    uartHandle = huart;
    customRxCallback = rxCallback;

    HAL_UART_Receive_IT(uartHandle, &rxBuffer[rxIndex], 1);
}

void serialSendMessage(const char *message)
{
    if (txQueue.count < TX_QUEUE_SIZE)
    {
        snprintf(txQueue.messageList[txQueue.end], sizeof(txQueue.messageList[txQueue.end]), "%s\r\n", message);

        txQueue.end = (txQueue.end + 1) % TX_QUEUE_SIZE;
        txQueue.count++;

        HAL_UART_Transmit_IT(uartHandle, (const uint8_t *)txQueue.messageList[txQueue.start], strlen(txQueue.messageList[txQueue.start]));
    }
}

bool serialCheckCommand(const char *message)
{
    if (strcmp((char *)rxBuffer, message) == 0)
    {
        return true;
    }

    return false;
}
