// Source
#include "sd_card.h"

// Private
SdFs sdFs;

// Public
bool sdCardInit()
{
    if (!sdFs.begin(SD_CS_PIN))
    {
        Serial.println("sd_card.cpp - Error: sdCardInit().");

        return false;
    }

    return true;
}

void sdCardOpen(const char *filePath, int mode, Callback callback)
{
    FsFile fileOpen = sdFs.open(filePath, mode);

    if (fileOpen)
    {
        callback(fileOpen);

        fileOpen.close();
    }
    else
    {
        Serial.println("sd_card.cpp - Error: sdCardOpen().");
    }
}

void sdCardList(const char *path)
{
    FsFile fileOpen = sdFs.open(path);

    if (fileOpen)
    {
        Serial.println("sd_card.cpp - Info: sdCardList().");

        while (true)
        {
            FsFile item = fileOpen.openNextFile();

            if (!item)
            {
                break;
            }

            char filename[13];
            item.getName(filename, 13);

            if (strlen(filename) > 0)
            {
                Serial.print("Filename: ");
                Serial.println(filename);
            }

            item.close();
        }

        fileOpen.close();
    }
    else
    {
        Serial.println("sd_card.cpp - Error: sdCardList().");
    }
}

void sdCardFormat()
{
    sdFs.end();

    if (!sdFs.format())
    {
        Serial.println("sd_card.cpp - Error: sdCardFormat().");

        return;
    }

    Serial.println("sd_card.cpp - Info: sdCardFormat() - Formatting successful.");
}
