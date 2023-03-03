/*!
 * @file        Board_APM32F407_EVAL.h
 *
 * @brief       This file contains definitions for APM32F407_EVAL's Leds, push-buttons hardware resources
 *
 * @version     V1.0.0
 *
 * @date        2022-05-25
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef __BOARD_APM32F407_EVAL_H
#define __BOARD_APM32F407_EVAL_H

#ifdef __cplusplus
  extern "C" {
#endif

#include "apm32f4xx.h"
#include "apm32f4xx_gpio.h"
#include "apm32f4xx_rcm.h"
#include "apm32f4xx_eint.h"
#include "apm32f4xx_usart.h"
#include "apm32f4xx_misc.h"
#include "apm32f4xx_syscfg.h"
#include "apm32f4xx_dma.h"
#include "apm32f4Xx_sdio.h"
#include "apm32f4xx_dci.h"
#include "apm32f4xx_smc.h"

/** @defgroup APM32F407_EVAL_Exported_Types
  * @{
  */
typedef enum
{
    LED1 = 0,
    LED2 = 1,
    LED3 = 2
} Led_TypeDef;

typedef enum
{
    BUTTON_KEY1 = 0,
    BUTTON_KEY2 = 1,
    BUTTON_KEY3 = 2,
    BUTTON_KEY4 = 3
} Button_TypeDef;

typedef enum
{
    BUTTON_MODE_GPIO = 0,
    BUTTON_MODE_EINT = 1
} ButtonMode_TypeDef;

typedef enum
{
    COM1 = 0,
    COM2 = 1,
    COM3 = 2
} COM_TypeDef;

/**
 * @brief   gpio port source define
 */
typedef enum
{
   GPIO_PORT_SOURCE_A,
   GPIO_PORT_SOURCE_B,
   GPIO_PORT_SOURCE_C,
   GPIO_PORT_SOURCE_D,
   GPIO_PORT_SOURCE_E,
   GPIO_PORT_SOURCE_F,
   GPIO_PORT_SOURCE_G,
}GPIO_PORT_SOURCE_T;

/** @addtogroup APM32F407_EVAL_LED
  * @{
  */
#define LEDn                             3

#define LED1_PIN                         GPIO_PIN_0
#define LED1_GPIO_PORT                   GPIOC
#define LED1_GPIO_CLK                    RCM_AHB1_PERIPH_GPIOC

#define LED2_PIN                         GPIO_PIN_2
#define LED2_GPIO_PORT                   GPIOC
#define LED2_GPIO_CLK                    RCM_AHB1_PERIPH_GPIOC

#define LED3_PIN                         GPIO_PIN_3
#define LED3_GPIO_PORT                   GPIOC
#define LED3_GPIO_CLK                    RCM_AHB1_PERIPH_GPIOC

/**
  * @}
  */

/** @addtogroup APM32F407_EVAL_BUTTON
  * @{
  */
#define BUTTONn                          4

/**
 * @brief Key1 push-button
 */
#define KEY1_BUTTON_PIN                   GPIO_PIN_0
#define KEY1_BUTTON_GPIO_PORT             GPIOB
#define KEY1_BUTTON_GPIO_CLK              RCM_AHB1_PERIPH_GPIOB
#define KEY1_BUTTON_EINT_LINE             EINT_LINE_0
#define KEY1_BUTTON_EINT_PORT_SOURCE      SYSCFG_PORT_GPIOB
#define KEY1_BUTTON_EINT_PIN_SOURCE       SYSCFG_PIN_0
#define KEY1_BUTTON_EINT_IRQn             EINT0_IRQn

/**
 * @brief Key2 push-button
 */
#define KEY2_BUTTON_PIN                   GPIO_PIN_1
#define KEY2_BUTTON_GPIO_PORT             GPIOB
#define KEY2_BUTTON_GPIO_CLK              RCM_AHB1_PERIPH_GPIOB
#define KEY2_BUTTON_EINT_LINE             EINT_LINE_1
#define KEY2_BUTTON_EINT_PORT_SOURCE      SYSCFG_PORT_GPIOB
#define KEY2_BUTTON_EINT_PIN_SOURCE       SYSCFG_PIN_1
#define KEY2_BUTTON_EINT_IRQn             EINT1_IRQn

/**
 * @brief Key3 push-button
 */
#define KEY3_BUTTON_PIN                   GPIO_PIN_12
#define KEY3_BUTTON_GPIO_PORT             GPIOF
#define KEY3_BUTTON_GPIO_CLK              RCM_AHB1_PERIPH_GPIOF
#define KEY3_BUTTON_EINT_LINE             EINT_LINE_12
#define KEY3_BUTTON_EINT_PORT_SOURCE      SYSCFG_PORT_GPIOF
#define KEY3_BUTTON_EINT_PIN_SOURCE       SYSCFG_PIN_12
#define KEY3_BUTTON_EINT_IRQn             EINT15_10_IRQn

/**
 * @brief Key4 push-button
 */
#define KEY4_BUTTON_PIN                   GPIO_PIN_5
#define KEY4_BUTTON_GPIO_PORT             GPIOA
#define KEY4_BUTTON_GPIO_CLK              RCM_AHB1_PERIPH_GPIOA
#define KEY4_BUTTON_EINT_LINE             EINT_LINE_5
#define KEY4_BUTTON_EINT_PORT_SOURCE      SYSCFG_PORT_GPIOA
#define KEY4_BUTTON_EINT_PIN_SOURCE       SYSCFG_PIN_5
#define KEY4_BUTTON_EINT_IRQn             EINT15_10_IRQn

/**
  * @}
  */

/** @addtogroup APM32F407_EVAL_COM
  * @{
  */
#define COMn                            3

/**
 * @brief Definition for COM port1, connected to USART1
 */
#define EVAL_COM1                        USART1
#define EVAL_COM1_CLK                    RCM_APB2_PERIPH_USART1
#define EVAL_COM1_TX_PIN                 GPIO_PIN_9
#define EVAL_COM1_TX_GPIO_PORT           GPIOA
#define EVAL_COM1_TX_GPIO_CLK            RCM_AHB1_PERIPH_GPIOA
#define EVAL_COM1_TX_PIN_SOURCE          GPIO_PIN_SOURCE_9
#define EVAL_COM1_RX_PIN                 GPIO_PIN_10
#define EVAL_COM1_RX_GPIO_PORT           GPIOA
#define EVAL_COM1_RX_GPIO_CLK            RCM_AHB1_PERIPH_GPIOA
#define EVAL_COM1_RX_PIN_SOURCE          GPIO_PIN_SOURCE_10
#define EVAL_COM1_IRQn                   USART1_IRQn
#define EVAL_COM1_GPIO_AF                GPIO_AF_USART1

/**
 * @brief Definition for COM port2, connected to USART2
 */
#define EVAL_COM2                        USART2
#define EVAL_COM2_CLK                    RCM_APB1_PERIPH_USART2
#define EVAL_COM2_TX_PIN                 GPIO_PIN_2
#define EVAL_COM2_TX_GPIO_PORT           GPIOA
#define EVAL_COM2_TX_PIN_SOURCE          GPIO_PIN_SOURCE_2
#define EVAL_COM2_TX_GPIO_CLK            RCM_AHB1_PERIPH_GPIOA
#define EVAL_COM2_RX_PIN                 GPIO_PIN_3
#define EVAL_COM2_RX_GPIO_PORT           GPIOA
#define EVAL_COM2_RX_GPIO_CLK            RCM_AHB1_PERIPH_GPIOA
#define EVAL_COM2_RX_PIN_SOURCE          GPIO_PIN_SOURCE_3
#define EVAL_COM2_IRQn                   USART2_IRQn
#define EVAL_COM2_GPIO_AF                GPIO_AF_USART2

/**
 * @brief Definition for COM port2, connected to USART3
 */
#define EVAL_COM3                        USART3
#define EVAL_COM3_CLK                    RCM_APB1_PERIPH_USART3
#define EVAL_COM3_TX_PIN                 GPIO_PIN_10
#define EVAL_COM3_TX_GPIO_PORT           GPIOB
#define EVAL_COM3_TX_PIN_SOURCE          GPIO_PIN_SOURCE_10
#define EVAL_COM3_TX_GPIO_CLK            RCM_AHB1_PERIPH_GPIOB

#define EVAL_COM3_RX_PIN                 GPIO_PIN_11
#define EVAL_COM3_RX_GPIO_PORT           GPIOB
#define EVAL_COM3_RX_GPIO_CLK            RCM_AHB1_PERIPH_GPIOB
#define EVAL_COM3_RX_PIN_SOURCE          GPIO_PIN_SOURCE_11
#define EVAL_COM3_IRQn                   USART3_IRQn
#define EVAL_COM3_GPIO_AF                GPIO_AF_USART3

/**
  * @}
  */

/** @addtogroup APM32F407_EVAL_BUZZER
  * @{
  */

#define EVAL_BUZZER_PIN                  GPIO_PIN_7
#define EVAL_BUZZER_GPIO_PORT            GPIOG
#define EVAL_BUZZER_GPIO_CLK             RCM_AHB1_PERIPH_GPIOG

/**
  * @}
  */
  

/** @defgroup APM32F407_EVAL_Exported_Functions
  * @{
  */
void APM_EVAL_LEDInit(Led_TypeDef Led);
void APM_EVAL_LEDOn(Led_TypeDef Led);
void APM_EVAL_LEDOff(Led_TypeDef Led);
void APM_EVAL_LEDToggle(Led_TypeDef Led);

void APM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t APM_EVAL_PBGetState(Button_TypeDef Button);

void APM_EVAL_COMInit(COM_TypeDef COM, USART_Config_T* configStruct);

void APM_EVAL_BuzzerInit(void);
void APM_EVAL_BuzzerOn(void);
void APM_EVAL_BuzzerOff(void);
void APM_EVAL_BuzzerToggle(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_APM32F407_EVAL_H */
