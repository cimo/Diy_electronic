// Source
#include "sd_spi_command.h"

// Private
void writeCallback()
{
    //...
}

void readCallback()
{
    //...
}

void removeCallback()
{
    //...
}

// Public
void sdSpiCommandInit()
{
    if (sdSpiMount())
    {
        sdSpiSpace();

        // sdSpiWrite("test.txt", FA_CREATE_NEW | FA_WRITE, "text\n", writeCallback);

        // sdSpiRead("test.txt", readCallback);

        // sdSpiWrite("test.txt", FA_OPEN_EXISTING | FA_READ | FA_WRITE, "text 1\n", writeCallback);

        // sdSpiRead("test.txt", readCallback);

        // sdSpiDelete("test.txt", removeCallback);

        sdSpiFileList("", false);

        // sdSpiUnmount();
    }
}

void sdSpiCommandLoop()
{
    //...
}
