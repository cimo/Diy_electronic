#include <Arduino.h>

// Source
#include "helper.h"
#include "display_i2c_command.h"
// #include "sd_spi_command.h"

/*
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
*/

uint32_t previousTimeLed = 0;
uint32_t previousTimeI2cLcd = 0;
uint32_t previousTimeTmc2209 = 0;

HardwareSerial Serial3(PB11, PB10);
HardwareTimer *htim2 = new HardwareTimer(TIM2);

#define MOTOR_X_ADDRESS 0x01
#define MOTOR_X_EN PA0
#define MOTOR_X_DIR PA1
#define MOTOR_X_STEP PA2

#define TMC2209_SYNC 0x05
#define TMC2209_READ 0x7F
#define TMC2209_WRITE 0x80

#define TMC2209_GCONF 0x00
#define TMC2209_IHOLD_IRUN 0x10
#define TMC2209_DRVSTATUS 0x6F

const uint16_t rmsCurrent = 800;
const uint16_t stepRevolution = 200; // 1.8°
const uint16_t microstep = 32;       // 1, 2, 4, 8, 16, 32, 64, 128, 256
const uint32_t stepTotal = stepRevolution * microstep;
volatile uint16_t stepCount = 0;

void serialSendMessage(const char *format, ...)
{
    char buffer[255];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    Serial.println(buffer);
}

void htim2Init()
{
    htim2->setOverflow(100, MICROSEC_FORMAT);

    htim2->attachInterrupt([]()
                           {
        static bool stepState = false;

        if (stepCount >= stepTotal)
        {
            return;
        }

        //tmc2209Step(MOTOR_X_ADDRESS, stepState);
        //digitalWrite(MOTOR_X_STEP, stepState);

        stepState = !stepState;

        if (!stepState)
        {
            stepCount++;
        } });

    htim2->resume();
}

uint8_t tmc2209_calcCRC(uint8_t *data, uint8_t length)
{
    uint8_t crc = 0;

    for (int a = 0; a < length; a++)
    {
        crc ^= data[a];

        for (int b = 0; b < 8; b++)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ 0x07;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}

void tmc2209_writeInt(uint8_t slaveAddress, uint8_t regAddress, uint32_t value)
{
    uint8_t data[8];

    data[0] = 0x05;
    data[1] = slaveAddress & 0xFF;
    data[2] = regAddress | 0x80;
    data[3] = (value >> 0) & 0xFF;
    data[4] = (value >> 8) & 0xFF;
    data[5] = (value >> 16) & 0xFF;
    data[6] = (value >> 24) & 0xFF;
    data[7] = tmc2209_calcCRC(data, 7);

    Serial3.write(data, 8);
}

bool tmc2209_readInt(uint8_t slaveAddress, uint8_t regAddress, uint32_t &valueOut)
{
    uint8_t request[4];

    request[0] = 0x05;
    request[1] = slaveAddress & 0xFF;
    request[2] = regAddress & 0x7F;
    request[3] = tmc2209_calcCRC(request, 3);

    Serial3.write(request, 4);

    delay(10);

    uint8_t response[6];
    int bytesRead = 0;

    while (bytesRead < 6)
    {
        if (Serial3.available())
        {
            response[bytesRead] = Serial3.read();

            Serial.print("Byte[");
            Serial.print(bytesRead);
            Serial.print("] = 0x");
            Serial.println(response[bytesRead], HEX);

            bytesRead++;
        }

        delay(1);
    }

    if (bytesRead != 6)
    {
        Serial.println("Errore BYTE!");

        return false;
    }

    if (tmc2209_calcCRC(response, 5) != response[5])
    {
        Serial.println("Errore CRC!");
        Serial.print("CRC Atteso: 0x");
        Serial.println(tmc2209_calcCRC(response, 5), HEX);
        Serial.print("CRC Ricevuto: 0x");
        Serial.println(response[5], HEX);

        return false;
    }

    valueOut = (uint32_t)response[1] |
               ((uint32_t)response[2] << 8) |
               ((uint32_t)response[3] << 16) |
               ((uint32_t)response[4] << 24);

    return true;
}

void tmc2209_disable(uint8_t slaveAddress)
{
    uint32_t value = (0 << 0) | (0 << 8) | (5 << 16); // ihold=0, irun=0, delay=5

    tmc2209_writeInt(slaveAddress, TMC2209_IHOLD_IRUN, value);
}

void tmc2209_enable(uint8_t slaveAddress)
{
    uint32_t value = (8 << 0) | (31 << 8) | (5 << 16); // ihold=8, irun=31, delay=5

    tmc2209_writeInt(slaveAddress, TMC2209_IHOLD_IRUN, value);
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(PB10, OUTPUT);
    pinMode(PB11, OUTPUT);

    pinMode(MOTOR_X_EN, OUTPUT);
    pinMode(MOTOR_X_DIR, OUTPUT);
    pinMode(MOTOR_X_STEP, OUTPUT);

    Serial.begin(9600);

    // Serial3.setHalfDuplex();
    // Serial3.isHalfDuplex();
    // Serial3.enableHalfDuplexRx();
    Serial3.begin(115200);

    while (!Serial && !Serial3)
    {
        delay(10);
    }

    Serial.println("Program started.");

    lcdI2cCommandInit();

    // sdCardCommandInit();
    /*
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
    */

    htim2Init();

    // digitalWrite(MOTOR_X_EN, LOW);
    // tmc2209Current(MOTOR_X_ADDRESS, 5, 31, 8);
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

    Serial.println("TMC2209 test start.");

    tmc2209_enable(MOTOR_X_ADDRESS);

    delay(10);

    uint32_t val;
    tmc2209_readInt(MOTOR_X_ADDRESS, TMC2209_IHOLD_IRUN, val);

    Serial.println("Test complete.");

    delay(1000);
}
