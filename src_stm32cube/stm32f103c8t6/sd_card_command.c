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
    sdCardInit();
    // sdCardOpen("test.txt", FA_CREATE_ALWAYS | FA_WRITE, openCallback);
}

void sdCardCommandLoop()
{
    //...
}
