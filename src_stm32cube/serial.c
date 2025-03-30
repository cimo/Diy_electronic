// Source
#include "serial.h"

// Private
UART_HandleTypeDef *uartHandle1 = NULL;
SerialCustomRxCallback customRxCallback = NULL;

uint8_t rxBuffer[SERIAL_BUFFER_SIZE];
uint8_t rxIndex = 0;

typedef struct MessageNode
{
    char *data;
    struct MessageNode *next;
} MessageNode;

MessageNode *messageNodeReused = NULL;
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
        if (rxIndex < SERIAL_BUFFER_SIZE - 1)
        {
            rxIndex++;
        }
        else
        {
            rxBufferReset();

            serialSendMessage("%s", localizationCurrent->uartError_bufferOverflow);
        }
    }

    HAL_UART_Receive_DMA(uartHandle1, &rxBuffer[rxIndex], 1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandle1->Instance)
    {
        MessageNode *oldNode = messageHead;
        messageHead = messageHead->next;

        free(oldNode->data);

        oldNode->next = messageNodeReused;
        messageNodeReused = oldNode;

        if (messageHead)
        {
            HAL_UART_Transmit_DMA(uartHandle1, (uint8_t *)messageHead->data, strlen(messageHead->data));
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
    if (huart->Instance == uartHandle1->Instance)
    {
        rxBufferReset();

        serialSendMessage("%s", localizationCurrent->uartError_generalFailure);

        HAL_UART_Receive_DMA(uartHandle1, &rxBuffer[rxIndex], 1);
    }
}

// Public
void serialInit(UART_HandleTypeDef *huart, SerialCustomRxCallback rxCallback)
{
    uartHandle1 = huart;
    customRxCallback = rxCallback;

    HAL_UART_Receive_DMA(uartHandle1, &rxBuffer[rxIndex], 1);
}

void serialSendMessage(const char *format, ...)
{
    va_list argumentList;
    va_list argumentListCopy;

    va_start(argumentList, format);

    va_copy(argumentListCopy, argumentList);
    int messageLength = vsnprintf(NULL, 0, format, argumentList);

    va_end(argumentList);

    if (messageLength < 0)
    {
        va_end(argumentListCopy);

        return;
    }

    char *messageFormatted = (char *)calloc(messageLength + 2, 1);

    if (!messageFormatted)
    {
        va_end(argumentListCopy);

        return;
    }

    vsnprintf(messageFormatted, messageLength + 1, format, argumentListCopy);
    va_end(argumentListCopy);

    messageFormatted[messageLength] = '\n';
    messageFormatted[messageLength + 1] = '\0';

    MessageNode *newNode;

    if (messageNodeReused)
    {
        newNode = messageNodeReused;
        messageNodeReused = messageNodeReused->next;
    }
    else
    {
        newNode = (MessageNode *)malloc(sizeof(MessageNode));

        if (!newNode)
        {
            free(messageFormatted);

            return;
        }
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

        HAL_UART_Transmit_DMA(uartHandle1, (uint8_t *)messageHead->data, strlen(messageHead->data));
    }
}

bool serialReceiveMessageCheck(const char *message)
{
    if (strcmp((char *)rxBuffer, message) == 0)
    {
        return true;
    }

    return false;
}
