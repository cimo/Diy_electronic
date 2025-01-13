// Source
#include "i2c_lcd.h"

// Private
FontDef_t *font = NULL;
SSD1306_COLOR_t color = 0x01;
uint8_t lineTotal = 0;
uint8_t bufferTotal = 0;

// Public
void i2cLcdInit(FontDef_t *fontValue, int16_t lineTotalValue, int16_t bufferTotalValue)
{
    font = fontValue;
    lineTotal = lineTotalValue;
    bufferTotal = bufferTotalValue;

    SSD1306_Init();
}

void i2cLcdClear()
{
    SSD1306_Clear();
}

void i2cLcdText(char *text, uint16_t column, uint16_t row)
{
    SSD1306_GotoXY(column, row * 10);
    SSD1306_Puts(text, font, color);
    SSD1306_UpdateScreen();
}

void i2cLcdTextScrollHorizontal(char *text, int index, uint16_t column, uint16_t row)
{
    static bool *isStartedList = NULL;
    static int16_t *columnList = NULL;
    static int16_t *rowList = NULL;
    static size_t *textLengthList = NULL;
    static int16_t *currentPositionList = NULL;

    if (isStartedList == NULL)
    {
        isStartedList = (bool *)calloc(lineTotal, sizeof(bool));
        columnList = (int16_t *)calloc(lineTotal, sizeof(int16_t));
        rowList = (int16_t *)calloc(lineTotal, sizeof(int16_t));
        textLengthList = (size_t *)calloc(lineTotal, sizeof(size_t));
        currentPositionList = (int16_t *)calloc(lineTotal, sizeof(int16_t));

        SSD1306_Clear();
    }

    if (!isStartedList[index])
    {
        isStartedList[index] = true;
        columnList[index] = column;
        rowList[index] = row * 10;
        textLengthList[index] = strlen(text);
        currentPositionList[index] = column;

        SSD1306_GotoXY(columnList[index], rowList[index]);
        SSD1306_Puts(text, font, color);
    }
    else
    {
        SSD1306_GotoXY(columnList[index], rowList[index]);

        for (int a = 0; a < textLengthList[index]; a++)
        {
            SSD1306_Puts(" ", font, color);
        }

        if (currentPositionList[index] < textLengthList[index])
        {
            currentPositionList[index]++;
        }
        else
        {
            currentPositionList[index] = columnList[index] - 1;
        }

        SSD1306_GotoXY(columnList[index], rowList[index]);
        SSD1306_Puts(text + currentPositionList[index], font, color);
    }

    SSD1306_UpdateScreen();
}

void i2cLcdTextScrollVertical(char *text, int index, uint16_t column, uint16_t row)
{
    static bool *isStartedList = NULL;
    static int16_t *columnList = NULL;
    static int16_t *rowList = NULL;
    static size_t *textLengthList = NULL;

    if (isStartedList == NULL)
    {
        isStartedList = (bool *)calloc(lineTotal, sizeof(bool));
        columnList = (int16_t *)calloc(lineTotal, sizeof(int16_t));
        rowList = (int16_t *)calloc(lineTotal, sizeof(int16_t));
        textLengthList = (size_t *)calloc(lineTotal, sizeof(size_t));

        SSD1306_Clear();
    }

    if (!isStartedList[index])
    {
        isStartedList[index] = true;
        columnList[index] = column;
        rowList[index] = row * 10;
        textLengthList[index] = strlen(text);

        SSD1306_GotoXY(columnList[index], rowList[index]);
        SSD1306_Puts(text, font, color);
    }
    else
    {
        SSD1306_GotoXY(columnList[index], rowList[index]);

        for (int a = 0; a < textLengthList[index]; a++)
        {
            SSD1306_Puts(" ", font, color);
        }

        if (rowList[index] <= 0)
        {
            rowList[index] = lineTotal * 10;
        }
        else
        {
            rowList[index] -= 10;
        }

        SSD1306_GotoXY(columnList[index], rowList[index]);
        SSD1306_Puts(text, font, color);
    }

    SSD1306_UpdateScreen();
}

void i2cLcdTextScrollVerticalBuffer(char *messageList[], uint16_t column)
{
    static bool isStarted = false;
    static uint8_t row = 1;

    SSD1306_Clear();

    if (!isStarted)
    {
        isStarted = true;

        for (uint16_t a = 0; a < lineTotal; a++)
        {
            SSD1306_GotoXY(column, a * 10);
            SSD1306_Puts(messageList[a], font, color);
        }
    }
    else
    {
        for (uint8_t a = 0; a < lineTotal; a++)
        {
            int messageLength = strlen(messageList[(row + a - 1) % bufferTotal]);

            SSD1306_GotoXY(column, a * 10);

            for (int b = 0; b <= messageLength; b++)
            {
                SSD1306_Puts(" ", font, color);
            }
        }

        for (uint16_t a = 0; a < lineTotal; a++)
        {
            SSD1306_GotoXY(column, a * 10);
            SSD1306_Puts(messageList[(row + a) % bufferTotal], font, color);
        }

        row = (row + 1) % bufferTotal;
    }

    SSD1306_UpdateScreen();
}
