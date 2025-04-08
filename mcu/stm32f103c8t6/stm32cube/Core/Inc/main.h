/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_1_Pin GPIO_PIN_13
#define LED_1_GPIO_Port GPIOC
#define GPIO_C_A0_Pin GPIO_PIN_0
#define GPIO_C_A0_GPIO_Port GPIOA
#define GPIO_C_A1_Pin GPIO_PIN_1
#define GPIO_C_A1_GPIO_Port GPIOA
#define GPIO_C_A2_Pin GPIO_PIN_2
#define GPIO_C_A2_GPIO_Port GPIOA
#define GPIO_C_A3_Pin GPIO_PIN_3
#define GPIO_C_A3_GPIO_Port GPIOA
#define GPIO_C_A4_Pin GPIO_PIN_4
#define GPIO_C_A4_GPIO_Port GPIOA
#define GPIO_C_A5_Pin GPIO_PIN_5
#define GPIO_C_A5_GPIO_Port GPIOA
#define GPIO_C_A6_Pin GPIO_PIN_6
#define GPIO_C_A6_GPIO_Port GPIOA
#define GPIO_C_A7_Pin GPIO_PIN_7
#define GPIO_C_A7_GPIO_Port GPIOA
#define GPIO_C_B0_Pin GPIO_PIN_0
#define GPIO_C_B0_GPIO_Port GPIOB
#define GPIO_C_B1_Pin GPIO_PIN_1
#define GPIO_C_B1_GPIO_Port GPIOB
#define GPIO_C_B2_Pin GPIO_PIN_2
#define GPIO_C_B2_GPIO_Port GPIOB
#define SD_SPI_CS_Pin GPIO_PIN_12
#define SD_SPI_CS_GPIO_Port GPIOB
#define GPIO_C_A8_Pin GPIO_PIN_8
#define GPIO_C_A8_GPIO_Port GPIOA
#define GPIO_C_B3_Pin GPIO_PIN_3
#define GPIO_C_B3_GPIO_Port GPIOB
#define GPIO_C_B4_Pin GPIO_PIN_4
#define GPIO_C_B4_GPIO_Port GPIOB
#define GPIO_C_B5_Pin GPIO_PIN_5
#define GPIO_C_B5_GPIO_Port GPIOB
#define GPIO_C_B8_Pin GPIO_PIN_8
#define GPIO_C_B8_GPIO_Port GPIOB
#define GPIO_C_B9_Pin GPIO_PIN_9
#define GPIO_C_B9_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
