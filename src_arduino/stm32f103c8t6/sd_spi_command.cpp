// Source
#include "sd_spi_command.h"

// Private
void openCallback(FsFile &fsFile)
{
    fsFile.println("cimo");

    Serial.println("SD write ok.");
}

// Public
void sdCardCommandInit()
{
    if (!sdCardInit(PB0))
    {
        return;
    }

    // sdCardOpen("test.txt", FILE_WRITE, openCallback);

    sdCardList("/");
}

void sdCardCommandLoop()
{
    //...
}
