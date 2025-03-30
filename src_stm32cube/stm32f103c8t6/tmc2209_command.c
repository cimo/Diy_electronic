// Source
#include "tmc2209_command.h"

// Private

// Public
void tmc2209CommandInit(UART_HandleTypeDef *huart)
{
    tmc2209Init(huart);

    uint32_t registerData = tmc2209RegisterRead(TMC2209_REGISTER_STATUS);

    if (registerData & TMC2209_STATUS_DRV_ERR)
        serialSendMessage("%s", "TMC2209 message: Driver error.");
    if (registerData & TMC2209_STATUS_UVLO)
        serialSendMessage("%s", "TMC2209 message: Under-voltage lockout.");
    if (registerData & TMC2209_STATUS_OVERTEMP)
        serialSendMessage("%s", "TMC2209 message: Over-temperature.");
    if (registerData & TMC2209_STATUS_OVERCURRENT)
        serialSendMessage("%s", "TMC2209 message: Over-current protection.");
    if (registerData & TMC2209_STATUS_SHORT_TO_GND)
        serialSendMessage("%s", "TMC2209 message: Short to GND.");
    if (registerData & TMC2209_STATUS_SHORT_TO_VCC)
        serialSendMessage("%s", "TMC2209 message: Short to VCC.");
}
