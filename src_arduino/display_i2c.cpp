// Source
#include "display_i2c.h"

// Private
SSD1306AsciiWire display;

uint8_t lineTotal = 0;
uint8_t bufferTotal = 0;

// Public
void i2cLcdInit(const DevType *driver, const int8_t address, const uint8_t *font, int16_t width, int16_t height, int16_t lineTotalValue, int16_t bufferTotalValue)
{
    DISPLAY_I2C_WIDTH = width;
    DISPLAY_I2C_HEIGHT = height;

    lineTotal = lineTotalValue;
    bufferTotal = bufferTotalValue;

    Wire.setSDA(PB7);
    Wire.setSCL(PB6);
    Wire.begin();

    display.begin(driver, address);
    display.setFont(font);
}

void i2cLcdClear()
{
    display.clear();
}

void i2cLcdText(const char *text, uint8_t column, uint8_t row)
{
    if ((DISPLAY_I2C_WIDTH == 0 && DISPLAY_I2C_HEIGHT == 0) || row > lineTotal)
    {
        return;
    }

    display.setCursor(column, row);
    display.print(text);
}

void i2cLcdTextScrollHorizontal(char *text, int index, uint8_t column, uint8_t row)
{
    if ((DISPLAY_I2C_WIDTH == 0 && DISPLAY_I2C_HEIGHT == 0) || row > lineTotal)
    {
        return;
    }

    static bool *isStartedList = new bool[lineTotal]();
    static int16_t *columnList = new int16_t[lineTotal]();
    static int16_t *rowList = new int16_t[lineTotal]();
    static size_t *textLengthList = new size_t[lineTotal]();
    static int16_t *currentPositionList = new int16_t[lineTotal]();

    if (!isStartedList[index])
    {
        isStartedList[index] = true;
        columnList[index] = column;
        rowList[index] = row;
        textLengthList[index] = strlen(text);
        currentPositionList[index] = column;

        display.setCursor(columnList[index], rowList[index]);
        display.print(text);
    }
    else
    {
        display.setCursor(columnList[index], rowList[index]);

        for (int a = 0; a < textLengthList[index]; a++)
        {
            display.print(" ");
        }

        if (currentPositionList[index] < textLengthList[index])
        {
            currentPositionList[index]++;
        }
        else
        {
            currentPositionList[index] = columnList[index];
        }

        display.setCursor(columnList[index], rowList[index]);
        display.print(text + currentPositionList[index]);
    }
}

void i2cLcdTextScrollVertical(char *text, int index, uint8_t column, uint8_t row)
{
    if ((DISPLAY_I2C_WIDTH == 0 && DISPLAY_I2C_HEIGHT == 0) || row > lineTotal)
    {
        return;
    }

    static bool *isStartedList = new bool[lineTotal]();
    static int16_t *columnList = new int16_t[lineTotal]();
    static int16_t *rowList = new int16_t[lineTotal]();
    static size_t *textLengthList = new size_t[lineTotal]();

    if (!isStartedList[index])
    {
        isStartedList[index] = true;
        columnList[index] = column;
        rowList[index] = row;
        textLengthList[index] = strlen(text);

        display.setCursor(columnList[index], rowList[index]);
        display.print(text);
    }
    else
    {
        display.setCursor(columnList[index], rowList[index]);

        for (int a = 0; a < textLengthList[index]; a++)
        {
            display.print(" ");
        }

        if (rowList[index] <= 0)
        {
            rowList[index] = lineTotal;
        }
        else
        {
            rowList[index]--;
        }

        display.setCursor(columnList[index], rowList[index]);
        display.print(text);
    }
}

void i2cLcdTextScrollVerticalBuffer(char *messageList[], uint8_t column)
{
    if (DISPLAY_I2C_WIDTH == 0 && DISPLAY_I2C_HEIGHT == 0)
    {
        return;
    }

    static bool isStarted = false;
    static uint8_t row = 1;

    if (!isStarted)
    {
        isStarted = true;

        for (uint8_t a = 0; a < lineTotal; a++)
        {
            display.setCursor(column, a);
            display.print(messageList[a]);
        }
    }
    else
    {
        for (uint8_t a = 0; a < lineTotal; a++)
        {
            int messageLength = strlen(messageList[(row + a - 1) % bufferTotal]);

            display.setCursor(column, a);

            for (int b = 0; b <= messageLength; b++)
            {
                display.print(" ");
            }
        }

        for (uint8_t a = 0; a < lineTotal; a++)
        {
            display.setCursor(column, a);
            display.print(messageList[(row + a) % bufferTotal]);
        }

        row = (row + 1) % bufferTotal;
    }
}
