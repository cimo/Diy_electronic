#include <stdbool.h>
#include <string.h>

// Source
#include "localization.h"

// Private
const Word localization_EN;
const Word localization_IT;

// Public
const Word localization_EN = {
    .uartError_bufferOverflow = "UART error: Buffer overflow.",
    .uartError_generalFailure = "UART error: General failure.",
    .uartInfo_unknownCommand = "UART info: Unknown command.",
    .serialMessage_led1On = "LED1: On.",
    .serialMessage_led1Off = "LED1: Off.",
    .serialMessage_programStarted = "Program started."};

const Word localization_IT = {
    .uartError_bufferOverflow = "UART errore: Buffer superato.",
    .uartError_generalFailure = "UART error: Fallimento generale.",
    .uartInfo_unknownCommand = "UART info: Comando non riconosciuto.",
    .serialMessage_led1On = "LED1: Accesso.",
    .serialMessage_led1Off = "LED1: Spento.",
    .serialMessage_programStarted = "Programma avviato."};

void localizationInit(const char *value)
{
    if (strcmp(value, "EN") == 0)
    {
        localizationCurrent = &localization_EN;
    }
    else if (strcmp(value, "IT") == 0)
    {
        localizationCurrent = &localization_IT;
    }
    else
    {
        localizationCurrent = &localization_EN;
    }
}
