#include <Arduino.h>

// Source
// #include "sd_card.h"
// #include "sd_card_command.h"
#include "i2c_lcd.h"

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);

    while (!Serial)
        ;

    Serial.println("Program started.");

    /*if (!sdCardInit(PB0))
    {
        return;
    }

    sdCardOpen("test.txt", FILE_WRITE, sdCardOpenCallback);

    sdCardList("/");*/

    i2cLcdInit(&SH1106_128x64, 0x3C, System5x7);
    i2cLcdText("stm32f103c8t6");

    //  i2cLcdTextScrollHorizontal("Test 1234567890-1234567890", 50);

    // const char *lineList[] = {"Line 1", "Line 2", "Line 3", "Line 4", "Line 5", "Line 6", "Line 7"};
    // i2cLcdTextScrollVertical(lineList, 200);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);

    delay(1000);

    digitalWrite(LED_BUILTIN, LOW);

    delay(1000);
}
