// Source
#include "serial.h"

// Private
UART_HandleTypeDef *uartHandleAsynchronous = NULL;
SerialRxCallbackAsynchronous rxCallbackAsynchronous = NULL;

uint8_t rxBufferAsynchronous[SERIAL_BUFFER_SIZE];
uint8_t rxIndexAsynchronous = 0;
uint8_t dmaBusyAsynchronous = false;

UART_HandleTypeDef *uartHandleSingleWire = NULL;
SerialRxCallbackSingleWire rxCallbackSingleWire = NULL;

uint8_t rxBufferSingleWire[SERIAL_BUFFER_SIZE];
uint8_t rxIndexSingleWire = 0;

typedef struct MessageNode
{
    char *data;
    struct MessageNode *next;
} MessageNode;

MessageNode *messageNodeReused = NULL;
MessageNode *messageHead = NULL;
MessageNode *messageTail = NULL;

void rxBufferResetAsynchronous()
{
    memset(rxBufferAsynchronous, 0, sizeof(rxBufferAsynchronous));
    rxIndexAsynchronous = 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandleAsynchronous->Instance)
    {
        if (rxBufferAsynchronous[rxIndexAsynchronous] == '\n')
        {
            rxBufferAsynchronous[rxIndexAsynchronous] = '\0';

            if (rxCallbackAsynchronous != NULL)
            {
                rxCallbackAsynchronous();
            }

            rxBufferResetAsynchronous();
        }
        else
        {
            rxIndexAsynchronous++;

            if (rxIndexAsynchronous >= sizeof(rxBufferAsynchronous) - 1)
            {
                rxBufferResetAsynchronous();

                serialAsynchronousSendMessage(localizationCurrent->uartError_bufferOverflow);
            }
        }

        HAL_UART_Receive_DMA(uartHandleAsynchronous, &rxBufferAsynchronous[rxIndexAsynchronous], 1);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandleAsynchronous->Instance)
    {
        MessageNode *oldNode = messageHead;
        messageHead = messageHead->next;

        free(oldNode->data);

        oldNode->next = messageNodeReused;
        messageNodeReused = oldNode;

        if (messageHead)
        {
            HAL_UART_Transmit_DMA(uartHandleAsynchronous, (uint8_t *)messageHead->data, strlen(messageHead->data));
        }
        else
        {
            dmaBusyAsynchronous = false;

            messageTail = NULL;
        }
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == uartHandleAsynchronous->Instance)
    {
        rxBufferResetAsynchronous();

        serialAsynchronousSendMessage(localizationCurrent->uartError_generalFailure);

        HAL_UART_Receive_DMA(uartHandleAsynchronous, &rxBufferAsynchronous[rxIndexAsynchronous], 1);
    }
}

void rxBufferResetSingleWire()
{
    memset(rxBufferSingleWire, 0, sizeof(rxBufferSingleWire));
    rxIndexSingleWire = 0;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == uartHandleSingleWire->Instance)
    {
        if (rxBufferSingleWire[rxIndexSingleWire] == '\n')
        {
            rxBufferSingleWire[rxIndexSingleWire] = '\0';

            if (rxCallbackSingleWire != NULL)
            {
                rxCallbackSingleWire();
            }

            rxBufferResetSingleWire();
        }
        else
        {
            rxIndexSingleWire++;

            if (rxIndexSingleWire >= sizeof(rxBufferSingleWire) - 1)
            {
                rxBufferResetSingleWire();
            }
        }

        HAL_UARTEx_ReceiveToIdle_IT(uartHandleSingleWire, &rxBufferSingleWire[rxIndexSingleWire], 1);
    }
}

// Public
void serialAsynchronousInit(UART_HandleTypeDef *huart, SerialRxCallbackAsynchronous rxCallback)
{
    uartHandleAsynchronous = huart;
    rxCallbackAsynchronous = rxCallback;

    rxBufferResetAsynchronous();

    HAL_UART_Receive_DMA(uartHandleAsynchronous, &rxBufferAsynchronous[rxIndexAsynchronous], 1);
}

void serialAsynchronousSendMessage(const char *format, ...)
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

    if (!dmaBusyAsynchronous)
    {
        dmaBusyAsynchronous = true;

        HAL_UART_Transmit_DMA(uartHandleAsynchronous, (uint8_t *)messageHead->data, strlen(messageHead->data));
    }
}

bool serialAsynchronousReceiveMessageCheck(const char *message)
{
    if (strcmp((char *)rxBufferAsynchronous, message) == 0)
    {
        return true;
    }

    return false;
}

void serialSingleWireInit(UART_HandleTypeDef *huart, SerialRxCallbackSingleWire rxCallback)
{
    uartHandleSingleWire = huart;
    rxCallbackSingleWire = rxCallback;

    rxBufferResetSingleWire();

    HAL_HalfDuplex_EnableReceiver(uartHandleSingleWire);
    HAL_UARTEx_ReceiveToIdle_IT(uartHandleSingleWire, &rxBufferSingleWire[rxIndexSingleWire], 1);
}

void serialSingleWireSendMessage(const char *format, ...)
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

    __disable_irq();
    HAL_HalfDuplex_EnableTransmitter(uartHandleSingleWire);
    HAL_UART_Transmit(uartHandleSingleWire, (uint8_t *)messageFormatted, strlen(messageFormatted), 1000);
    HAL_HalfDuplex_EnableReceiver(uartHandleSingleWire);
    __enable_irq();
}

bool serialSingleWireReceiveMessageCheck(const char *message)
{
    if (strcmp((char *)rxBufferSingleWire, message) == 0)
    {
        return true;
    }

    return false;
}
