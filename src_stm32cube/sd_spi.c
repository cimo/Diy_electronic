// Source
#include "sd_spi.h"

// Private
FATFS fatFsMount;
FATFS *fatFsSpace = &fatFsMount;
FRESULT fResult;
UINT read, write;
DWORD freeCluster;
DIR dir;
FIL fil;
FILINFO fileInfo;

char bufferFileData[SERIAL_BUFFER_SIZE];

const char *errorCodeMessage()
{
    switch (fResult)
    {
    case FR_DISK_ERR:
        return localizationCurrent->sdSpiError_code1;
    case FR_INT_ERR:
        return localizationCurrent->sdSpiError_code2;
    case FR_NOT_READY:
        return localizationCurrent->sdSpiError_code3;
    case FR_NO_FILE:
        return localizationCurrent->sdSpiError_code4;
    case FR_NO_PATH:
        return localizationCurrent->sdSpiError_code5;
    case FR_INVALID_NAME:
        return localizationCurrent->sdSpiError_code6;
    case FR_DENIED:
        return localizationCurrent->sdSpiError_code7;
    case FR_EXIST:
        return localizationCurrent->sdSpiError_code8;
    case FR_INVALID_OBJECT:
        return localizationCurrent->sdSpiError_code9;
    case FR_WRITE_PROTECTED:
        return localizationCurrent->sdSpiError_code10;
    case FR_INVALID_DRIVE:
        return localizationCurrent->sdSpiError_code11;
    case FR_NOT_ENABLED:
        return localizationCurrent->sdSpiError_code12;
    case FR_NO_FILESYSTEM:
        return localizationCurrent->sdSpiError_code13;
    case FR_MKFS_ABORTED:
        return localizationCurrent->sdSpiError_code14;
    case FR_TIMEOUT:
        return localizationCurrent->sdSpiError_code15;
    case FR_LOCKED:
        return localizationCurrent->sdSpiError_code16;
    case FR_NOT_ENOUGH_CORE:
        return localizationCurrent->sdSpiError_code17;
    case FR_TOO_MANY_OPEN_FILES:
        return localizationCurrent->sdSpiError_code18;
    case FR_INVALID_PARAMETER:
        return localizationCurrent->sdSpiError_code19;
    default:
        return localizationCurrent->genericError;
    }
}

bool open(const char *filePath, uint8_t mode)
{
    fResult = f_open(&fil, filePath, mode);

    if (fResult != FR_OK)
    {
        serialAsynchronousSendMessage("%s%s\n", localizationCurrent->sdSpiError_open, errorCodeMessage());

        fResult = f_close(&fil);

        return false;
    }

    return true;
}

void bufferFileDataClear()
{
    for (uint8_t a = 0; a < SERIAL_BUFFER_SIZE; a++)
    {
        bufferFileData[a] = '\0';
    }
}

// Public
bool sdSpiMount()
{
    fResult = f_mount(&fatFsMount, "", 1);

    if (fResult != FR_OK)
    {
        serialAsynchronousSendMessage("%s%s\n", localizationCurrent->sdSpiError_mount, errorCodeMessage());

        return false;
    }

    return true;
}

void sdSpiSpace()
{
    fResult = f_getfree("", &freeCluster, &fatFsSpace);

    if (fResult != FR_OK)
    {
        serialAsynchronousSendMessage("%s%s\n", localizationCurrent->sdSpiError_getfree, errorCodeMessage());

        fResult = f_close(&fil);

        return;
    }

    uint64_t spaceTotal = ((uint64_t)(fatFsMount.n_fatent - 2) * fatFsMount.csize * 512);
    uint64_t spaceFree = ((uint64_t)freeCluster * fatFsMount.csize * 512);
    uint64_t spaceUsed = spaceTotal - spaceFree;

    const char *spaceTotalUnit = helperConvertSizeUnit(spaceTotal);
    serialAsynchronousSendMessage("%s%s", localizationCurrent->sdSpiInfo_spaceTotal, spaceTotalUnit);

    const char *spaceFreeUnit = helperConvertSizeUnit(spaceFree);
    serialAsynchronousSendMessage("%s%s", localizationCurrent->sdSpiInfo_spaceFree, spaceFreeUnit);

    const char *spaceUsedUnit = helperConvertSizeUnit(spaceUsed);
    serialAsynchronousSendMessage("%s%s", localizationCurrent->sdSpiInfo_spaceUsed, spaceUsedUnit);
}

void sdSpiDirectoryList(const char *path, bool isShowHidden)
{
    fResult = f_opendir(&dir, path);

    if (fResult != FR_OK)
    {
        serialAsynchronousSendMessage("%s%s\n", localizationCurrent->sdSpiError_open_dir, errorCodeMessage());

        fResult = f_closedir(&dir);

        return;
    }

    serialAsynchronousSendMessage(localizationCurrent->sdSpiInfo_directoryList);

    while (1)
    {
        fResult = f_readdir(&dir, &fileInfo);

        if (fResult != FR_OK || fileInfo.fname[0] == 0)
        {
            break;
        }

        if (!isShowHidden && (fileInfo.fattrib & AM_HID))
        {
            continue;
        }

        const char tagDirectory = (fileInfo.fattrib & AM_DIR) ? 'D' : '-';
        const char tagReadOnly = (fileInfo.fattrib & AM_RDO) ? 'R' : '-';
        const char tagSystem = (fileInfo.fattrib & AM_SYS) ? 'S' : '-';
        const char tagHidden = (fileInfo.fattrib & AM_HID) ? 'H' : '-';

        static char bufferName[_MAX_LFN + 1];
        fileInfo.lfname = bufferName;
        fileInfo.lfsize = sizeof(bufferName);

        const char *size = helperConvertSizeUnit(fileInfo.fsize);
        const char *name = fileInfo.lfname[0] ? fileInfo.lfname : fileInfo.fname;

        serialAsynchronousSendMessage("%c%c%c%c %s %s/%s", tagDirectory, tagReadOnly, tagSystem, tagHidden, size, path, name);
    }

    fResult = f_closedir(&dir);
}

void sdSpiWrite(const char *filePath, const char *data, bool isAppend, sdSpiCallback callback)
{
    fResult = f_stat(filePath, &fileInfo);

    uint8_t mode = 0;

    if (fResult == FR_NO_FILE)
    {
        if (isAppend)
        {
            mode = FA_CREATE_NEW | FA_READ | FA_WRITE;
        }
        else
        {
            mode = FA_CREATE_NEW | FA_WRITE;
        }
    }
    else
    {
        if (isAppend)
        {
            mode = FA_OPEN_EXISTING | FA_READ | FA_WRITE;
        }
        else
        {
            mode = FA_OPEN_EXISTING | FA_WRITE;
        }
    }

    bool isOpen = open(filePath, mode);

    if (isOpen && fResult == FR_OK)
    {
        if (isAppend)
        {
            fResult = f_lseek(&fil, f_size(&fil));

            if (fResult != FR_OK)
            {
                serialAsynchronousSendMessage("%s%s\n", localizationCurrent->sdSpiError_lseek, errorCodeMessage());

                fResult = f_close(&fil);

                return;
            }
        }

        fResult = f_write(&fil, data, strlen(data), &write);

        if (fResult != FR_OK)
        {
            serialAsynchronousSendMessage("%s%s\n", localizationCurrent->sdSpiError_write, errorCodeMessage());

            fResult = f_close(&fil);

            return;
        }

        fResult = f_close(&fil);

        callback();
    }
}

void sdSpiRead(const char *filePath, sdSpiCallback callback)
{
    bool isOpen = open(filePath, FA_READ);

    if (isOpen)
    {
        fResult = f_read(&fil, bufferFileData, f_size(&fil), &read);

        if (fResult != FR_OK)
        {
            serialAsynchronousSendMessage("%s%s\n", localizationCurrent->sdSpiError_read, errorCodeMessage());

            fResult = f_close(&fil);

            return;
        }

        fResult = f_close(&fil);

        serialAsynchronousSendMessage("%s\n%s", localizationCurrent->sdSpiInfo_fileData, bufferFileData);

        bufferFileDataClear();

        callback();
    }
}

void sdSpiDelete(const char *filePath, sdSpiCallback callback)
{
    fResult = f_unlink(filePath);

    if (fResult != FR_OK)
    {
        serialAsynchronousSendMessage("%s%s\n", localizationCurrent->sdSpiError_unlink, errorCodeMessage());

        fResult = f_close(&fil);

        return;
    }

    fResult = f_close(&fil);

    callback();
}

bool sdSpiUnmount()
{
    fResult = f_mount(NULL, "", 1);

    if (fResult != FR_OK)
    {
        serialAsynchronousSendMessage("%s%s\n", localizationCurrent->sdSpiError_mount, errorCodeMessage());

        return false;
    }

    return true;
}
