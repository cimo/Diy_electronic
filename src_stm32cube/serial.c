// Source
#include "serial.h"

// Private
UART_HandleTypeDef *uartHandle = NULL;
SerialCustomRxCallback customRxCallback = NULL;

uint8_t rxBuffer[RX_BUFFER_SIZE];
uint8_t rxIndex = 0;

typedef struct MessageNode
{
    char *data;
    struct MessageNode *next;
} MessageNode;

MessageNode *messageHead = NULL;
MessageNode *messageTail = NULL;

uint8_t dmaBusy = false;

void rxBufferReset()
{
    memset(rxBuffer, 0, sizeof(rxBuffer));
    rxIndex = 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
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
        if (rxIndex < RX_BUFFER_SIZE - 1)
        {
            rxIndex++;
        }
        else
        {
            rxBufferReset();

            serialSendMessage(localizationCurrent->uartError_bufferOverflow);
        }
    }

    HAL_UART_Receive_DMA(uartHandle, &rxBuffer[rxIndex], 1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandle->Instance)
    {
        MessageNode *oldNode = messageHead;
        messageHead = messageHead->next;

        free(oldNode->data);
        free(oldNode);

        if (messageHead)
        {
            HAL_UART_Transmit_DMA(uartHandle, (uint8_t *)messageHead->data, strlen(messageHead->data));
        }
        else
        {
            dmaBusy = false;

            messageTail = NULL;
        }
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandle->Instance)
    {
        rxBufferReset();

        serialSendMessage(localizationCurrent->uartError_generalFailure);

        HAL_UART_Receive_DMA(uartHandle, &rxBuffer[rxIndex], 1);
    }
}

// Public
void serialInit(UART_HandleTypeDef *huart, SerialCustomRxCallback rxCallback)
{
    uartHandle = huart;
    customRxCallback = rxCallback;

    HAL_UART_Receive_DMA(uartHandle, &rxBuffer[rxIndex], 1);
}

void serialSendMessage(const char *message)
{
    char *messageFormatted = (char *)malloc(strlen(message) + 2);

    if (!messageFormatted)
    {
        return;
    }

    strcpy(messageFormatted, message);
    messageFormatted[strlen(message)] = '\n';
    messageFormatted[strlen(message) + 1] = '\0';

    MessageNode *newNode = (MessageNode *)malloc(sizeof(MessageNode));

    if (!newNode)
    {
        free(messageFormatted);

        return;
    }

    newNode->data = messageFormatted;
    newNode->next = NULL;

    if (!messageTail)
    {
        messageHead = messageTail = newNode;
    }
    else
    {
        messageTail->next = newNode;
        messageTail = newNode;
    }

    if (!dmaBusy)
    {
        dmaBusy = true;

        HAL_UART_Transmit_DMA(uartHandle, (uint8_t *)messageHead->data, strlen(messageHead->data));
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
