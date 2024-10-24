#include <Arduino.h>

// Source
#include "sd_card.h"
// #include "lcd.h"

void sdCardOpenCallback(FsFile &file)
{
    file.println("cimo");
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(57600);

    while (!Serial)
        ;

    Serial.println("Program started.");

    if (!sdCardInit())
    {
        return;
    }

    sdCardOpen("test.txt", FILE_WRITE, sdCardOpenCallback);

    sdCardList("/");

    /*if (!lcdInit())
    {
        return;
    }

    lcdDraw();*/
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);

    delay(1000);

    digitalWrite(LED_BUILTIN, LOW);

    delay(1000);
}
