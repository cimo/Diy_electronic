// Source
#include "sd_card_command.h"

// Private

// Public
void sdCardOpenCallback(FIL *file)
{
    f_puts("cimo", file);

    serialSendMessage("SD write ok.");
}
