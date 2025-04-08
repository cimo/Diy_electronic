// Source
#include "serial_command.h"

// Private
void initCallback()
{
    if (serialReceiveMessageCheck("led_1_on"))
    {
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);

        serialSendMessage(localizationCurrent->serialMessage_led1On);
    }
    else if (serialReceiveMessageCheck("led_1_off"))
    {
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);

        serialSendMessage(localizationCurrent->serialMessage_led1Off);
    }
    else
    {
        serialSendMessage(localizationCurrent->uartInfo_unknownCommand);
    }
}

// Public
void serialCommandInit(UART_HandleTypeDef *huart)
{
    serialInit(huart, initCallback);

    serialSendMessage(localizationCurrent->serialMessage_programStarted);
}
