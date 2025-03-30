// Source
#include "tmc2209.h"

// Private
UART_HandleTypeDef *uartHandle2 = NULL;

uint8_t calculateCrc(uint8_t *data, uint8_t length)
{
    uint8_t crc = 0;

    for (uint8_t a = 0; a < length; a++)
    {
        crc ^= data[a];

        for (uint8_t b = 0; b < 8; b++)
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

// Public
void tmc2209Init(UART_HandleTypeDef *huart)
{
    uartHandle2 = huart;
}

void tmc2209RegisterWrite(uint8_t registerAddress, uint32_t data)
{
    uint8_t command[6];

    command[0] = registerAddress;
    command[1] = (uint8_t)(data >> 24);
    command[2] = (uint8_t)(data >> 16);
    command[3] = (uint8_t)(data >> 8);
    command[4] = (uint8_t)(data & 0xFF);

    uint8_t crc = calculateCrc(command, 5);
    command[5] = crc;

    HAL_UART_Transmit_IT(uartHandle2, command, sizeof(command));
}

uint32_t tmc2209RegisterRead(uint8_t registerAddress)
{
    uint8_t command[2];
    uint8_t response[6];

    command[0] = registerAddress;
    command[1] = 0x00;

    uint8_t crc = calculateCrc(command, 1);
    command[1] = crc;

    HAL_UART_Transmit_IT(uartHandle2, command, sizeof(command));

    HAL_UART_Receive_IT(uartHandle2, response, sizeof(response));

    uint32_t data = 0;

    data |= (response[1] << 24);
    data |= (response[2] << 16);
    data |= (response[3] << 8);
    data |= response[4];

    return data;
}
