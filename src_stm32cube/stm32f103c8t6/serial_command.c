#include "main.h"

// Source
#include "src_stm32cube/localization.h"
#include "src_stm32cube/serial.h"
#include "serial_command.h"

// Private

// Public
void serialCommand()
{
    if (serialCheckCommand("led1_on"))
    {
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

        serialSendMessage(localizationCurrent->serialMessage_led1On);
    }
    else if (serialCheckCommand("led1_off"))
    {
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

        serialSendMessage(localizationCurrent->serialMessage_led1Off);
    }
    else
    {
        serialSendMessage(localizationCurrent->uartInfo_unknownCommand);
    }
}
