// Source
#include "sd_card.h"

// Private
SdFs sdFs;

// Public
bool sdCardInit(int pinNumber)
{
    if (!sdFs.begin(pinNumber))
    {
        Serial.println("sd_card.cpp - Error: sdCardInit().");

        return false;
    }

    return true;
}

void sdCardOpen(const char *filePath, int mode, SdCardOpenCallback callback)
{
    FsFile fsFile = sdFs.open(filePath, mode);

    if (!fsFile)
    {
        Serial.println("sd_card.cpp - Error: sdCardOpen().");
    }
    else
    {
        callback(fsFile);
    }

    fsFile.close();
}

void sdCardList(const char *path)
{
    FsFile fsFile = sdFs.open(path);

    if (!fsFile)
    {
        Serial.println("sd_card.cpp - Error: sdCardList().");
    }
    else
    {
        Serial.println("sd_card.cpp - Info: sdCardList().");

        while (true)
        {
            FsFile fsFileSub = fsFile.openNextFile();

            if (!fsFileSub)
            {
                break;
            }

            char filename[13];
            fsFileSub.getName(filename, 13);

            if (strlen(filename) > 0)
            {
                Serial.print("Filename: ");
                Serial.println(filename);
            }

            fsFileSub.close();
        }
    }

    fsFile.close();
}

void sdCardFormat()
{
    sdFs.end();

    if (!sdFs.format())
    {
        Serial.println("sd_card.cpp - Error: sdCardFormat().");
    }
    else
    {
        Serial.println("sd_card.cpp - Info: sdCardFormat() - Formatting successful.");
    }
}
