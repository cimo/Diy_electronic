// Source
#include "sd_card_command.h"

// Private

// Public
void sdCardOpenCallback(FsFile &fsFile)
{
    fsFile.println("cimo");

    Serial.println("Write in file completed.");
}
