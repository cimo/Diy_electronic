// Source
#include "serial_command.h"

// Private
void rxCallbackAsynchronousInit()
{
    if (serialAsynchronousReceiveMessageCheck("led_1_on"))
    {
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);

        serialAsynchronousSendMessage(localizationCurrent->serialMessage_led1On);
    }
    else if (serialAsynchronousReceiveMessageCheck("led_1_off"))
    {
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);

        serialAsynchronousSendMessage(localizationCurrent->serialMessage_led1Off);
    }
    else
    {
        serialAsynchronousSendMessage(localizationCurrent->uartInfo_unknownCommand);
    }
}

void rxCallbackSingleWireInit()
{
    if (serialSingleWireReceiveMessageCheck("test_message"))
    {
        serialSingleWireSendMessage("Received");
    }
}

// Public
void serialCommandAsynchronousInit(UART_HandleTypeDef *huart)
{
    serialAsynchronousInit(huart, rxCallbackAsynchronousInit);

    serialAsynchronousSendMessage(localizationCurrent->serialMessage_asynchronousStarted);
}

void serialCommandSingleWireInit(UART_HandleTypeDef *huart)
{
    serialSingleWireInit(huart, rxCallbackSingleWireInit);

    serialSingleWireSendMessage(localizationCurrent->serialMessage_singleWireStarted);
}
