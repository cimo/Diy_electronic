#include <Arduino.h>

// Source
#include "helper.h"
#include "display_i2c_command.h"
// #include "sd_spi_command.h"

unsigned long previousTimeLed = 0;
unsigned long previousTimei2cLcd = 0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);

    while (!Serial)
        ;

    Serial.println("Program started.");

    lcdI2cCommandInit();

    // sdCardCommandInit();
}

void loop()
{
    if (helperMillisecondElapsed(&previousTimeLed, 1000))
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }

    if (helperMillisecondElapsed(&previousTimei2cLcd, 500))
    {
        i2cLcdCommandLoop();
    }
}
