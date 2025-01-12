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
    SSD1306_GotoXY(column, row);
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
        rowList[index] = row;
        textLengthList[index] = strlen(text);
        currentPositionList[index] = column;

        SSD1306_GotoXY(columnList[index], rowList[index]);
        SSD1306_Puts(text, font, color);
    }
    else
    {
        SSD1306_GotoXY(columnList[index], rowList[index]);

        for (uint8_t a = 0; a < textLengthList[index]; a++)
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
    //...
}

void i2cLcdTextScrollVerticalBuffer(char *messages[], uint16_t column)
{
    //...
}
