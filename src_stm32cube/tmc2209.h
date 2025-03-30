#ifndef TMC2209_H
#define TMC2209_H

#include <stdio.h>
#include <string.h>
#include "stm32f1xx_hal.h"

#define TMC2209_UART_BAUDRATE 115200

#define TMC2209_REGISTER_GCONF 0x00      // General Configuration
#define TMC2209_REGISTER_CHOPCONF 0x06   // Chopper Configuration
#define TMC2209_REGISTER_TPOWERDOWN 0x11 // Power Down Time
#define TMC2209_REGISTER_TPWMTHRS 0x10   // PWM Threshold
#define TMC2209_REGISTER_IRUN 0x08       // Current Running
#define TMC2209_REGISTER_ICHOP 0x0C      // Chopper Current
#define TMC2209_REGISTER_IHOLD 0x10      // Hold Current
#define TMC2209_REGISTER_TSTEP 0x0A      // Step Timer
#define TMC2209_REGISTER_STATUS 0x80     // Status Register
#define TMC2209_REGISTER_DRV_STATUS 0x6F // Driver Status
#define TMC2209_REGISTER_SG_RESULT 0xA0  // StallGuard Result
#define TMC2209_REGISTER_RAMPMODE 0x30   // Ramp Mode
#define TMC2209_REGISTER_XDIRECT 0x2F    // Direct Command
#define TMC2209_REGISTER_PWMCONF 0x08    // PWM Configuration
#define TMC2209_REGISTER_TCCONF 0x1A     // TMC2209 Configuration
#define TMC2209_REGISTER_GSTAT 0xA5      // General Status
#define TMC2209_REGISTER_COOLCONF 0x1B   // CoolStep Configuration
#define TMC2209_REGISTER_VACTUAL 0x2F    // Actual Velocity
#define TMC2209_REGISTER_VMAX 0x26       // Maximum Velocity
#define TMC2209_REGISTER_BYPASS 0x35     // Bypass Mode

// GCONF
#define TMC2209_GCONF_FSTDBY (1 << 0)        // Stepper in standby
#define TMC2209_GCONF_EN_ERR (1 << 1)        // Enable error flag
#define TMC2209_GCONF_IHOLDDELAY (0x3F << 2) // Hold delay
#define TMC2209_GCONF_TPOWERDOWN (0x3F << 8) // Power-down time

// CHOPCONF
#define TMC2209_CHOPCONF_TOFF (0x0F << 0) // Off-time (chopper)
#define TMC2209_CHOPCONF_CHM (1 << 4)     // Chopper mode
#define TMC2209_CHOPCONF_VHIGH (1 << 5)   // High voltage setting
#define TMC2209_CHOPCONF_MRES (0x07 << 6) // Microstepping resolution
#define TMC2209_CHOPCONF_SDOFF (1 << 9)   // Stealth mode off

// TPOWERDOWN
#define TMC2209_TPOWERDOWN_TPDDIS (1 << 0)    // Disable power-down
#define TMC2209_TPOWERDOWN_TPDTIM (0x3F << 1) // Power-down time

// TPWMTHRS
#define TMC2209_TPWMTHRS_PWMTHRS (0xFFFF << 0) // PWM threshold

// IRUN
#define TMC2209_IRUN_IRUN (0x1F << 0) // Running current

// ICHOP
#define TMC2209_ICHOP_ICHOP (0x0F << 0) // Chopper current

// IHOLD
#define TMC2209_IHOLD_IHOLD (0x0F << 0) // Hold current

// TSTEP
#define TMC2209_TSTEP_TSTEP (0xFFFF << 0) // Step timer

// STATUS
#define TMC2209_STATUS_DRV_ERR (1 << 0)      // Driver error
#define TMC2209_STATUS_UVLO (1 << 1)         // Under-voltage lockout
#define TMC2209_STATUS_OVERTEMP (1 << 2)     // Over-temperature
#define TMC2209_STATUS_OVERCURRENT (1 << 3)  // Over-current protection
#define TMC2209_STATUS_SHORT_TO_GND (1 << 4) // Short to GND
#define TMC2209_STATUS_SHORT_TO_VCC (1 << 5) // Short to VCC

// DRV_STATUS
#define TMC2209_DRV_STATUS_STALLGUARD (1 << 15) // StallGuard result
#define TMC2209_DRV_STATUS_COOLSTEP (1 << 14)   // CoolStep active
#define TMC2209_DRV_STATUS_OPENLOAD (1 << 13)   // Open load detection
#define TMC2209_DRV_STATUS_OVERTEMP (1 << 12)   // Over-temperature
#define TMC2209_DRV_STATUS_SHORT_GND (1 << 9)   // Short to GND
#define TMC2209_DRV_STATUS_SHORT_VCC (1 << 8)   // Short to VCC

// SG_RESULT
#define TMC2209_SG_RESULT_SG_RESULT (0xFF << 0) // StallGuard result

// RAMPMODE
#define TMC2209_RAMPMODE_MODE (0x03 << 0) // Ramp mode (e.g., linear, quadratic)

// XDIRECT
#define TMC2209_XDIRECT_CMD (0xFF << 0) // Direct command (used for debugging)

// PWMCONF
#define TMC2209_PWMCONF_PWM_FREQUENCY (0x0F << 0) // PWM frequency setting
#define TMC2209_PWMCONF_PWM_GRADIENT (0xFF << 4)  // PWM gradient

// TCCONF
#define TMC2209_TCCONF_MODE (0x03 << 0)   // Motor mode setting (e.g., standstill, full speed)
#define TMC2209_TCCONF_RAMPUP (0xFF << 2) // Ramp-up time configuration

// GSTAT
#define TMC2209_GSTAT_RESET (1 << 0) // Reset status

// COOLCONF
#define TMC2209_COOLCONF_TCC (0x0F << 0) // CoolStep threshold
#define TMC2209_COOLCONF_VSENSE (1 << 4) // Voltage sense mode

// VACTUAL
#define TMC2209_VACTUAL_VACTUAL (0xFFFF << 0) // Actual velocity (in steps/s)

// VMAX
#define TMC2209_VMAX_VMAX (0xFFFF << 0) // Maximum velocity (in steps/s)

// BYPASS
#define TMC2209_BYPASS_BYPASS_MODE (1 << 0) // Bypass mode for SPI communication

void tmc2209Init(UART_HandleTypeDef *huart);
void tmc2209RegisterWrite(uint8_t registerAddress, uint32_t data);
uint32_t tmc2209RegisterRead(uint8_t registerAddress);

#endif
