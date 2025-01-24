#include <Arduino.h>

// Source
// #include "sd_spi.h"
// #include "sd_spi_command.h"
#include "display_i2c.h"

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);

    while (!Serial)
        ;

    Serial.println("Program started.");

    /*if (!sdCardInit(4))
    {
        return;
    }

    sdCardOpen("test.txt", FILE_WRITE, sdCardOpenCallback);

    sdCardList("/");*/

    i2cLcdInit(&Adafruit128x64, 0x3C, System5x7);
    i2cLcdText("atmega328p");
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);

    delay(1000);

    digitalWrite(LED_BUILTIN, LOW);

    delay(1000);
}
