// Source
#include "sd_spi_command.h"

// Private

// Public
void sdCardOpenCallback(FsFile &fsFile)
{
    fsFile.println("cimo");

    Serial.println("Write in file completed.");
}
