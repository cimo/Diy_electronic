// Source
#include "sd_spi_command.h"

// Private
void openCallback(FIL *fil)
{
    sdCardPut("cimo");
}

// Public
void sdCardCommandInit()
{
    if (sdCardInit())
    {
        sdCardSpace();

        sdCardOpen("test.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ, openCallback);
    }
}

void sdCardCommandLoop()
{
    //...
}
