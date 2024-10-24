#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <stdbool.h>
#include <string.h>

typedef struct
{
    const char *uartError_bufferOverflow;
    const char *uartError_generalFailure;
    const char *uartInfo_unknownCommand;
    const char *serialMessage_led1On;
    const char *serialMessage_led1Off;
    const char *serialMessage_programStarted;
} Word;

const Word localization_EN;
const Word localization_IT;
const Word *localizationCurrent;

void localizationInit(const char *value);

#endif
