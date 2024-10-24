#include "main.h"

// Source
#include "localization.h"
#include "serial.h"
#include "serial_command.h"

// Private

// Public
void serialCommand()
{
    if (serialCheckCommand("led_1_on"))
    {
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);

        serialSendMessage(localizationCurrent->serialMessage_led1On);
    }
    else if (serialCheckCommand("led_1_off"))
    {
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);

        serialSendMessage(localizationCurrent->serialMessage_led1Off);
    }
    else
    {
        serialSendMessage(localizationCurrent->uartInfo_unknownCommand);
    }
}
