// Source
#include "tmc2209_command.h"

// Private
UART_HandleTypeDef *tmc2209UartHandle = NULL;
TIM_HandleTypeDef *tmc2209HtimHandle = NULL;

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

#define rmsCurrent 800
#define stepRevolution 200 // 1.8°
#define microstep 32       // 1, 2, 4, 8, 16, 32, 64, 128, 256
#define stepTotal (stepRevolution * microstep)
volatile uint16_t stepCount = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == tmc2209HtimHandle->Instance)
    {
        static bool stepState = false;

        if (stepCount >= stepTotal)
        {
            return;
        }

        // HAL_GPIO_WritePin(MOTOR_X_STEP_GPIO_Port, MOTOR_X_STEP_Pin, stepState ? GPIO_PIN_SET : GPIO_PIN_RESET);

        stepState = !stepState;

        if (!stepState)
        {
            stepCount++;

            // serialAsynchronousSendMessage("stepCount: [%lu]", stepCount);
        }
    }
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

    HAL_HalfDuplex_EnableTransmitter(tmc2209UartHandle);
    HAL_UART_Transmit(tmc2209UartHandle, data, 8, HAL_MAX_DELAY);

    HAL_Delay(10);

    HAL_HalfDuplex_EnableReceiver(tmc2209UartHandle);
}

bool tmc2209_readInt(uint8_t slaveAddress, uint8_t regAddress, uint32_t *valueOut)
{
    uint8_t request[4];

    request[0] = 0x05;
    request[1] = slaveAddress & 0xFF;
    request[2] = regAddress & 0x7F;
    request[3] = tmc2209_calcCRC(request, 3);

    HAL_HalfDuplex_EnableTransmitter(tmc2209UartHandle);
    HAL_UART_Transmit(tmc2209UartHandle, request, 4, HAL_MAX_DELAY);

    HAL_Delay(2);

    HAL_HalfDuplex_EnableReceiver(tmc2209UartHandle);

    uint8_t response[6];

    if (HAL_UART_Receive(tmc2209UartHandle, response, 6, 100) != HAL_OK)
    {
        serialAsynchronousSendMessage("Errore BYTE!");

        return false;
    }

    for (int i = 0; i < 6; i++)
    {
        serialAsynchronousSendMessage("response[%d] = 0x%02X", i, response[i]);
    }

    uint8_t crc = tmc2209_calcCRC(response, 5);

    if (crc != response[5])
    {
        serialAsynchronousSendMessage("Errore CRC!\nCRC Atteso: 0x%02X\nCRC Ricevuto: 0x%02X\n", crc, response[5]);

        return false;
    }

    *valueOut = (uint32_t)response[1] |
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

bool tmc2209_readDRVSTATUS(uint32_t *outValue)
{
    uint8_t request[4];
    request[0] = 0x05;
    request[1] = 0x01;
    request[2] = 0x6F & 0x7F;
    request[3] = tmc2209_calcCRC(request, 3);

    HAL_HalfDuplex_EnableTransmitter(tmc2209UartHandle);
    HAL_UART_Transmit(tmc2209UartHandle, request, 4, 100);

    HAL_Delay(10);

    uint8_t response[6];

    HAL_HalfDuplex_EnableReceiver(tmc2209UartHandle);
    if (HAL_UART_Receive(tmc2209UartHandle, response, 6, 100) != HAL_OK)
    {
        serialAsynchronousSendMessage("Errore ricezione DRVSTATUS!");
        return false;
    }

    uint8_t crc = tmc2209_calcCRC(response, 5);
    if (crc != response[5])
    {
        serialAsynchronousSendMessage("CRC ERRATO! Atteso: 0x%02X, Ricevuto: 0x%02X", crc, response[5]);
        return false;
    }

    *outValue = ((uint32_t)response[1]) |
                ((uint32_t)response[2] << 8) |
                ((uint32_t)response[3] << 16) |
                ((uint32_t)response[4] << 24);

    return true;
}

uint8_t UART3_RxBuffer[4];

/*void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == tmc2209UartHandle->Instance)
    {
        // serialAsynchronousSendMessage("cimo");
        // HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);

        // HAL_UARTEx_ReceiveToIdle_IT(tmc2209UartHandle, UART3_RxBuffer, sizeof(UART3_RxBuffer));
    }
}*/

// Public
void tmc2209CommandInit(UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim)
{
    tmc2209UartHandle = huart;
    tmc2209HtimHandle = htim;

    /*HAL_TIM_Base_Start_IT(tmc2209HtimHandle);

    serialAsynchronousSendMessage("TMC2209 test start.");

    tmc2209_enable(MOTOR_X_ADDRESS);

    HAL_Delay(10);

    uint32_t val;
    tmc2209_readInt(MOTOR_X_ADDRESS, TMC2209_IHOLD_IRUN, &val);

    serialAsynchronousSendMessage("TMC2209 test completed.");*/

    // HAL_UARTEx_ReceiveToIdle_IT(tmc2209UartHandle, UART3_RxBuffer, sizeof(UART3_RxBuffer));
}

void tmc2209CommandLoop()
{
    uint32_t drvStatus;
    if (tmc2209_readDRVSTATUS(&drvStatus))
    {
        serialAsynchronousSendMessage("DRVSTATUS: 0x%08lX", drvStatus);
    }
    else
    {
        serialAsynchronousSendMessage("Lettura DRVSTATUS fallita.");
    }

    HAL_Delay(1000);
}
