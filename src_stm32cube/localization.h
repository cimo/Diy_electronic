#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <stdbool.h>
#include <string.h>

typedef struct
{
    const char *uartError_bufferOverflow;
    const char *uartError_generalFailure;
    const char *uartInfo_unknownCommand;
    const char *serialMessage_programStarted;
    const char *serialMessage_led1On;
    const char *serialMessage_led1Off;
    const char *genericError;
    const char *sdSpiInfo_spaceTotal;
    const char *sdSpiInfo_spaceFree;
    const char *sdSpiInfo_spaceUsed;
    const char *sdSpiInfo_data;
    const char *sdSpiError_mount;
    const char *sdSpiError_open;
    const char *sdSpiError_getfree;
    const char *sdSpiError_lseek;
    const char *sdSpiError_write;
    const char *sdSpiError_read;
    const char *sdSpiError_open_dir;
    const char *sdSpiError_unlink;
    const char *sdSpiError_code1;
    const char *sdSpiError_code2;
    const char *sdSpiError_code3;
    const char *sdSpiError_code4;
    const char *sdSpiError_code5;
    const char *sdSpiError_code6;
    const char *sdSpiError_code7;
    const char *sdSpiError_code8;
    const char *sdSpiError_code9;
    const char *sdSpiError_code10;
    const char *sdSpiError_code11;
    const char *sdSpiError_code12;
    const char *sdSpiError_code13;
    const char *sdSpiError_code14;
    const char *sdSpiError_code15;
    const char *sdSpiError_code16;
    const char *sdSpiError_code17;
    const char *sdSpiError_code18;
    const char *sdSpiError_code19;
} Word;

const Word localization_EN;
const Word localization_IT;
const Word *localizationCurrent;

void localizationInit(const char *value);

#endif
