#include <Arduino.h>
// #include <TMCStepper.h>

// Source
#include "helper.h"
#include "display_i2c_command.h"
// #include "sd_spi_command.h"

#include <SPI.h>
#include <SdFat.h>

SdFat sd;

#define SD_CS_PIN PB12
static SPIClass mySPI2(PB15, PB14, PB13, SD_CS_PIN);
#define SD2_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(18), &mySPI2)

void printDirectory(File &dir, int numTabs)
{
    while (true)
    {

        File entry = dir.openNextFile();

        if (!entry)
        {
            // no more files
            break;
        }
        for (uint8_t i = 0; i < numTabs; i++)
        {
            Serial.print('\t');
        }
        entry.printName(&Serial);

        if (entry.isDirectory())
        {
            Serial.println("/");

            printDirectory(entry, numTabs + 1);
        }
        else
        {
            // files have sizes, directories do not
            Serial.print("\t\t");
            Serial.print(entry.size(), DEC);
            uint16_t pdate;
            uint16_t ptime;
            entry.getModifyDateTime(&pdate, &ptime);

            Serial.printf("\tLAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", FS_YEAR(pdate), FS_MONTH(pdate), FS_DAY(pdate), FS_HOUR(ptime), FS_MINUTE(ptime), FS_SECOND(ptime));
        }
        entry.close();
    }
}

uint32_t previousTimeLed = 0;
uint32_t previousTimeI2cLcd = 0;
uint32_t previousTimeTmc2209 = 0;

/* HardwareSerial huart2(USART2);
HardwareTimer *htim2 = new HardwareTimer(TIM2);

#define MOTOR_COUNT 1
#define MOTOR_X_EN_PIN PB1
#define MOTOR_X_DIR_PIN PA1
#define MOTOR_X_STEP_PIN PA0

#define TMC2209_SYNC 0x05
#define TMC2209_READ 0x80
#define TMC2209_WRITE 0x00

#define TMC2209_DRVSTATUS 0x6F

void serialSendMessage(const char *format, ...)
{
    char buffer[255];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    Serial.println(buffer);
}

uint8_t tmc2209Crc8(uint8_t *data, uint8_t length)
{
    uint8_t crc = 0;

    for (uint8_t i = 0; i < length; i++)
    {
        uint8_t currentByte = data[i];

        for (uint8_t j = 0; j < 8; j++)
        {
            if ((crc >> 7) ^ (currentByte & 0x01))
                crc = (crc << 1) ^ 0x07;
            else
                crc = (crc << 1);

            currentByte >>= 1;
        }
    }

    return crc;
}

void tmc2209RegisterWrite(uint8_t address, uint8_t reg, uint32_t data)
{
    uint8_t dataWrite[8];

    dataWrite[0] = TMC2209_SYNC;
    dataWrite[1] = address;
    dataWrite[2] = reg | TMC2209_WRITE;
    dataWrite[3] = (data >> 24) & 0xFF;
    dataWrite[4] = (data >> 16) & 0xFF;
    dataWrite[5] = (data >> 8) & 0xFF;
    dataWrite[6] = data & 0xFF;
    dataWrite[7] = tmc2209Crc8(dataWrite, 7);

    huart2.write(dataWrite, 8);
}

uint32_t tmc2209RegisterRead(uint8_t address, uint8_t reg)
{
    uint8_t dataWrite[4];
    uint8_t dataResponse[8];

    dataWrite[0] = TMC2209_SYNC;
    dataWrite[1] = address;
    dataWrite[2] = reg | TMC2209_READ;
    dataWrite[3] = tmc2209Crc8(dataWrite, 3);

    huart2.write(dataWrite, 4);

    delay(10);

    int bytesRead = 0;
    while (huart2.available() < 8 && bytesRead < 8)
    {
        bytesRead++;
    }

    for (int i = 0; i < 8; i++)
    {
        if (huart2.available())
        {
            dataResponse[i] = huart2.read();
        }
    }

    return ((uint32_t)dataResponse[4] << 24) |
           ((uint32_t)dataResponse[5] << 16) |
           ((uint32_t)dataResponse[6] << 8) |
           dataResponse[7];
}

void decodeDVRStatus(uint32_t value)
{
    serialSendMessage("DRVSTATUS: 0x%08lX", value);

    serialSendMessage("[%s] Overtemp warning", ((value >> 30) & 1) ? "x" : " ");
    serialSendMessage("[%s] Overtemp shutdown", ((value >> 27) & 1) ? "x" : " ");
    serialSendMessage("[%s] Short to GND A", ((value >> 26) & 1) ? "x" : " ");
    serialSendMessage("[%s] Short to GND B", ((value >> 25) & 1) ? "x" : " ");
    serialSendMessage("[%s] Open load A", ((value >> 24) & 1) ? "x" : " ");
    serialSendMessage("[%s] Open load B", ((value >> 23) & 1) ? "x" : " ");
    serialSendMessage("[%s] StallGuard triggered", ((value >> 22) & 1) ? "x" : " ");

    serialSendMessage("Actual current: %u", (value >> 16) & 0x1F);
    serialSendMessage("StallGuard value: %u", value & 0xFFFF);
}

TMC2209Stepper driver(&huart2, 0.11f, 0x00);
const uint16_t rmsCurrent = 600;
const uint16_t stepRevolution = 200; // 1.8°
const uint16_t microstep = 32;       // 1, 2, 4, 8, 16, 32, 64, 128, 256
const uint32_t stepTotal = stepRevolution * microstep;
volatile uint16_t stepCount = 0;

void Timer2Init()
{
    htim2->setOverflow(100, MICROSEC_FORMAT);

    htim2->attachInterrupt([]()
                           {
        static bool stepState = false;

        if (stepCount >= stepTotal)
            return;

        digitalWrite(MOTOR_X_STEP_PIN, stepState);

        stepState = !stepState;

        if (!stepState)
            stepCount++; });

    htim2->resume();
}*/

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    /*pinMode(MOTOR_X_EN_PIN, OUTPUT);
    pinMode(MOTOR_X_DIR_PIN, OUTPUT);
    pinMode(MOTOR_X_STEP_PIN, OUTPUT);*/

    Serial.begin(9600);
    /*huart2.begin(115200);

    while (!Serial && !huart2)
    {
        delay(10);
    }*/

    while (!Serial)
    {
        delay(10);
    }

    Serial.println("Program started.");

    lcdI2cCommandInit();

    // sdCardCommandInit();

    if (sd.begin(SD2_CONFIG))
    {
        uint32_t cardSize = sd.card()->sectorCount();

        // print the type of card
        Serial.println();
        Serial.print("Card type:         ");
        switch (sd.card()->type())
        {
        case SD_CARD_TYPE_SD1:
            Serial.println(F("SD1"));
            break;
        case SD_CARD_TYPE_SD2:
            Serial.println(F("SD2"));
            break;

        case SD_CARD_TYPE_SDHC:
            if (cardSize < 70000000)
            {
                Serial.println(F("SDHC"));
            }
            else
            {
                Serial.println(F("SDXC"));
            }
            break;

        default:
            Serial.println(F("Unknown"));
        }

        //  print the type and size of the first FAT-type volume
        uint32_t volumesize;
        Serial.print("Volume type is:    FAT");
        Serial.println(int(sd.vol()->fatType()), DEC);

        Serial.print("Card size:  ");
        Serial.println((float)0.000512 * cardSize);

        Serial.print("Total bytes: ");
        Serial.println(0.000512 * sd.vol()->clusterCount() * sd.sectorsPerCluster());

        Serial.print("Free bytes: ");
        Serial.println(0.000512 * sd.vol()->freeClusterCount() * sd.sectorsPerCluster());

        File dir = sd.open("/");

        printDirectory(dir, 0);
    }

    // tmc2209RegisterWrite(0x00, 0x10, 0x00);

    /*Timer2Init();

    // digitalWrite(MOTOR_X_EN_PIN, LOW);

    driver.begin();
    driver.rms_current(rmsCurrent);
    driver.microsteps(microstep);*/
}

void loop()
{
    if (helperMillisecondElapsed(&previousTimeLed, 100))
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }

    if (helperMillisecondElapsed(&previousTimeI2cLcd, 1000))
    {
        // i2cLcdCommandLoop();
    }

    if (helperMillisecondElapsed(&previousTimeTmc2209, 1000))
    {
        // uint32_t drvstatus = tmc2209RegisterRead(0x00, TMC2209_DRVSTATUS);
        // decodeDVRStatus(drvstatus);
    }
}
