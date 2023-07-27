/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define TP11_Pin GPIO_PIN_2
#define TP11_GPIO_Port GPIOE
#define TP12_Pin GPIO_PIN_3
#define TP12_GPIO_Port GPIOE
#define MCU_32K_OSC_IN_Pin GPIO_PIN_14
#define MCU_32K_OSC_IN_GPIO_Port GPIOC
#define MCU_32K_OSC_OUT_Pin GPIO_PIN_15
#define MCU_32K_OSC_OUT_GPIO_Port GPIOC
#define MCU_25M_OSC_IN_Pin GPIO_PIN_0
#define MCU_25M_OSC_IN_GPIO_Port GPIOH
#define MCU_25M_OSC_OUT_Pin GPIO_PIN_1
#define MCU_25M_OSC_OUT_GPIO_Port GPIOH
#define TP7_Pin GPIO_PIN_2
#define TP7_GPIO_Port GPIOC
#define TP8_Pin GPIO_PIN_3
#define TP8_GPIO_Port GPIOC
#define TP3_Pin GPIO_PIN_0
#define TP3_GPIO_Port GPIOA
#define TP1_Pin GPIO_PIN_1
#define TP1_GPIO_Port GPIOA
#define TP2_Pin GPIO_PIN_2
#define TP2_GPIO_Port GPIOA
#define TP4_Pin GPIO_PIN_3
#define TP4_GPIO_Port GPIOA
#define LED_BOOT_RED_Pin GPIO_PIN_13
#define LED_BOOT_RED_GPIO_Port GPIOD
#define MAG_IMU_I2C3_SDA_Pin GPIO_PIN_9
#define MAG_IMU_I2C3_SDA_GPIO_Port GPIOC
#define MAG_IMU_I2C3_SCL_Pin GPIO_PIN_8
#define MAG_IMU_I2C3_SCL_GPIO_Port GPIOA
#define DEBUG_SWDIO_Pin GPIO_PIN_13
#define DEBUG_SWDIO_GPIO_Port GPIOA
#define DEBUG_SWCLK_Pin GPIO_PIN_14
#define DEBUG_SWCLK_GPIO_Port GPIOA
#define WIDM_FDCAN1_RX_Pin GPIO_PIN_0
#define WIDM_FDCAN1_RX_GPIO_Port GPIOD
#define WIDM_FDCAN1_TX_Pin GPIO_PIN_1
#define WIDM_FDCAN1_TX_GPIO_Port GPIOD
#define MAG_IMU_RDY_Pin GPIO_PIN_3
#define MAG_IMU_RDY_GPIO_Port GPIOD
#define ACC_GYRO_IMU_I2C1_SCL_Pin GPIO_PIN_6
#define ACC_GYRO_IMU_I2C1_SCL_GPIO_Port GPIOB
#define ACC_GYTO_IMU_I2C1_SDA_Pin GPIO_PIN_7
#define ACC_GYTO_IMU_I2C1_SDA_GPIO_Port GPIOB
#define TP9_Pin GPIO_PIN_0
#define TP9_GPIO_Port GPIOE
#define TP10_Pin GPIO_PIN_1
#define TP10_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
