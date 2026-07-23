/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include"lcd.h"
#include "BUTTON.h"
#include "menu.h"
#include "dashboard.h"
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
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOC
#define LCD_DB4_Pin GPIO_PIN_7
#define LCD_DB4_GPIO_Port GPIOE
#define LCD_DB5_Pin GPIO_PIN_8
#define LCD_DB5_GPIO_Port GPIOE
#define LCD_DB6_Pin GPIO_PIN_9
#define LCD_DB6_GPIO_Port GPIOE
#define LCD_DB7_Pin GPIO_PIN_10
#define LCD_DB7_GPIO_Port GPIOE
#define LCD_RS_Pin GPIO_PIN_11
#define LCD_RS_GPIO_Port GPIOD
#define LCD_DB0_Pin GPIO_PIN_14
#define LCD_DB0_GPIO_Port GPIOD
#define LCD_DB1_Pin GPIO_PIN_15
#define LCD_DB1_GPIO_Port GPIOD
#define LCD_EN_Pin GPIO_PIN_7
#define LCD_EN_GPIO_Port GPIOC
#define SW6_Pin GPIO_PIN_9
#define SW6_GPIO_Port GPIOA
#define SW5_Pin GPIO_PIN_10
#define SW5_GPIO_Port GPIOA
#define SW4_Pin GPIO_PIN_15
#define SW4_GPIO_Port GPIOA
#define SW3_Pin GPIO_PIN_10
#define SW3_GPIO_Port GPIOC
#define SW2_Pin GPIO_PIN_11
#define SW2_GPIO_Port GPIOC
#define SW1_Pin GPIO_PIN_12
#define SW1_GPIO_Port GPIOC
#define LCD_DB2_Pin GPIO_PIN_0
#define LCD_DB2_GPIO_Port GPIOD
#define LCD_DB3_Pin GPIO_PIN_1
#define LCD_DB3_GPIO_Port GPIOD
#define LCD_RW_Pin GPIO_PIN_5
#define LCD_RW_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
