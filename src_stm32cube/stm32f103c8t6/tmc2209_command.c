// Source
#include "tmc2209_command.h"

// Private
/*
#define TMC2209_WRITE 0x80
#define TMC2209_READ 0x00
#define TMC2209_SYNC 0x05

#define TMC2209_IHOLD_IRUN 0x10
#define TMC2209_DRVSTATUS 0x6F

UART_HandleTypeDef *uart2Handle = NULL;
TIM_HandleTypeDef *tim2Handle = NULL;

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

    HAL_UART_Transmit(uart2Handle, dataWrite, 8, 100);
}

uint32_t tmc2209RegisterRead(uint8_t address, uint8_t reg)
{
    uint8_t dataWrite[4];
    uint8_t dataResponse[8];

    dataWrite[0] = TMC2209_SYNC;
    dataWrite[1] = address;
    dataWrite[2] = reg | TMC2209_READ;
    dataWrite[3] = tmc2209Crc8(dataWrite, 3);

    HAL_UART_Transmit(uart2Handle, dataWrite, 4, 100);

    HAL_UART_Receive(uart2Handle, dataResponse, 8, 100);

    return ((uint32_t)dataResponse[4] << 24) |
           ((uint32_t)dataResponse[5] << 16) |
           ((uint32_t)dataResponse[6] << 8) |
           dataResponse[7];
}

void tmc2209OutputDrvStatus(uint32_t value)
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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim2)
{
    if (htim2->Instance == tim2Handle->Instance)
    {
        static uint16_t step_counter = 0;

        if (++step_counter >= 50)
        {
            step_counter = 0;

            GPIO_PinState motorEnableState = HAL_GPIO_ReadPin(MOTOR_X_EN_GPIO_Port, MOTOR_X_EN_Pin);

            if (motorEnableState == GPIO_PIN_RESET)
            {
                serialSendMessage("Step HIGH");
                HAL_GPIO_WritePin(MOTOR_X_STEP_GPIO_Port, MOTOR_X_STEP_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(MOTOR_X_STEP_GPIO_Port, MOTOR_X_STEP_Pin, GPIO_PIN_RESET);
                serialSendMessage("Step LOW");
            }
        }
    }
}

// Public
void tmc2209CommandInit(UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim2)
{
    uart2Handle = huart;
    tim2Handle = htim2;

    HAL_TIM_Base_Start_IT(tim2Handle);

    tmc2209RegisterWrite(0x00, TMC2209_IHOLD_IRUN, (32 << 16) | (38 << 8) | 5);
    tmc2209RegisterWrite(0x00, 0x10, 0x00);

    HAL_GPIO_WritePin(MOTOR_X_EN_GPIO_Port, MOTOR_X_EN_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(MOTOR_X_DIR_GPIO_Port, MOTOR_X_DIR_Pin, GPIO_PIN_RESET);
}

void tmc2209CommandLoop()
{
    //...
}

void tmc2209Debug()
{
    uint32_t drvstatus = tmc2209RegisterRead(0x00, TMC2209_DRVSTATUS);

    tmc2209OutputDrvStatus(drvstatus);
}
*/
