/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

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
#define TempSense_Pin GPIO_PIN_0
#define TempSense_GPIO_Port GPIOA
#define ctrl1_Pin GPIO_PIN_1
#define ctrl1_GPIO_Port GPIOA
#define ctrl2_Pin GPIO_PIN_2
#define ctrl2_GPIO_Port GPIOA
#define hall1_Pin GPIO_PIN_3
#define hall1_GPIO_Port GPIOA
#define hall2_Pin GPIO_PIN_4
#define hall2_GPIO_Port GPIOA
#define hall3_Pin GPIO_PIN_5
#define hall3_GPIO_Port GPIOA
#define hall4_Pin GPIO_PIN_6
#define hall4_GPIO_Port GPIOA
#define powerCut_Pin GPIO_PIN_10
#define powerCut_GPIO_Port GPIOB
#define ctrl3_Pin GPIO_PIN_8
#define ctrl3_GPIO_Port GPIOA
#define ctrl4_Pin GPIO_PIN_9
#define ctrl4_GPIO_Port GPIOA
#define test1_Pin GPIO_PIN_6
#define test1_GPIO_Port GPIOB
#define test2_Pin GPIO_PIN_7
#define test2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
