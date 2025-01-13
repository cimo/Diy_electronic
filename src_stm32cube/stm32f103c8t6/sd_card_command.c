// Source
#include "sd_card_command.h"

// Private
void openCallback(FIL *file)
{
    f_puts("cimo", file);

    serialSendMessage("SD write ok.");
}

// Public
void sdCardCommandInit()
{
    if (!sdCardInit())
    {
        return;
    }

    sdCardOpen("test.txt", FA_WRITE, openCallback);
}

void sdCardCommandLoop()
{
    //...
}
