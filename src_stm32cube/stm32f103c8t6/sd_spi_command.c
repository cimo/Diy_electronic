// Source
#include "sd_spi_command.h"

// Private
void writeCallback()
{
    serialAsynchronousSendMessage(localizationCurrent->sdSpiInfo_writeCompleted);
}

void readCallback()
{
    serialAsynchronousSendMessage(localizationCurrent->sdSpiInfo_readCompleted);
}

void deleteCallback()
{
    serialAsynchronousSendMessage(localizationCurrent->sdSpiInfo_deleteCompleted);
}

// Public
void sdSpiCommandInit(SPI_HandleTypeDef *hspi)
{
    if (sdSpiMount())
    {
        sdSpiSpace();

        sdSpiDirectoryList("", false);

        // sdSpiWrite("test.txt", "cimo 1\n", true, writeCallback);

        // sdSpiRead("test.txt", readCallback);

        // sdSpiWrite("test1.txt", "cimo 2\n", false, writeCallback);

        // sdSpiRead("test1.txt", readCallback);

        // sdSpiDelete("test1.txt", deleteCallback);

        sdSpiUnmount();
    }
}
