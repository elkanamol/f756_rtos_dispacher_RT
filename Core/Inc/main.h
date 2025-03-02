/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern RNG_HandleTypeDef hrng;
extern UART_HandleTypeDef huart3;
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
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define DEBUG_AMBULANCE_PIN_Pin GPIO_PIN_3
#define DEBUG_AMBULANCE_PIN_GPIO_Port GPIOF
#define DEBUG_FIRE_PIN_Pin GPIO_PIN_5
#define DEBUG_FIRE_PIN_GPIO_Port GPIOF
#define DEBUG_CORONA_PIN_Pin GPIO_PIN_10
#define DEBUG_CORONA_PIN_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define DEBUG_DISPATCHER_PIN_Pin GPIO_PIN_0
#define DEBUG_DISPATCHER_PIN_GPIO_Port GPIOC
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define DEBUG_POLICE_PIN_Pin GPIO_PIN_3
#define DEBUG_POLICE_PIN_GPIO_Port GPIOC
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define DEBUG_EVENT_MANAGEMENT_PIN_Pin GPIO_PIN_3
#define DEBUG_EVENT_MANAGEMENT_PIN_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define SW0_Pin GPIO_PIN_3
#define SW0_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB

/* Debug configurations */
#define DEBUG_GPIO_TRACKING // Comment out to disable GPIO debug tracking

/* USER CODE BEGIN Private defines */
#ifdef DEBUG_GPIO_TRACKING
// LED Pins
#define DEBUG_EVENT_MANAGEMENT_LED LD1_Pin
#define DEBUG_DISPATCHER_LED LD2_Pin
#define DEBUG_ERROR_LED LD3_Pin

// Debug Pins
#define DEBUG_EVENT_MANAGEMENT_PIN GPIO_PIN_3
#define DEBUG_EVENT_MANAGEMENT_PORT GPIOA

#define DEBUG_DISPATCHER_PIN GPIO_PIN_0
#define DEBUG_DISPATCHER_PORT GPIOC

#define DEBUG_POLICE_PIN GPIO_PIN_3
#define DEBUG_POLICE_PORT GPIOC

#define DEBUG_AMBULANCE_PIN GPIO_PIN_3
#define DEBUG_AMBULANCE_PORT GPIOF

#define DEBUG_FIRE_PIN GPIO_PIN_5
#define DEBUG_FIRE_PORT GPIOF

#define DEBUG_CORONA_PIN GPIO_PIN_10
#define DEBUG_CORONA_PORT GPIOF

// Debug Macros
#define DEBUG_GPIO_ON(port, pin) HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET)
#define DEBUG_GPIO_OFF(port, pin) HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET)
#define DEBUG_GPIO_TOGGLE(port, pin) HAL_GPIO_TogglePin(port, pin)

// LED Macros
#define DEBUG_LED_TOGGLE(pin) HAL_GPIO_TogglePin(GPIOB, pin)
#define DEBUG_LED_ON(pin) HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_SET)
#else
#define DEBUG_GPIO_ON(port, pin) ((void)0)
#define DEBUG_GPIO_OFF(port, pin) ((void)0)
#define DEBUG_GPIO_TOGGLE(port, pin) ((void)0)
#define DEBUG_LED_TOGGLE(pin) ((void)0)
#endif
  /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
