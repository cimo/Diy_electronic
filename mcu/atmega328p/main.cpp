#include <Arduino.h>

// Source
// #include "sd_card.h"
// #include "sd_card_command.h"
#include "lcd.h"

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

    if (!lcdInit(128, 64, -1, 0x3C))
    {
        return;
    }

    lcdDraw();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);

    delay(1000);

    digitalWrite(LED_BUILTIN, LOW);

    delay(1000);
}
