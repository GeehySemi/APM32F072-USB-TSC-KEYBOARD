/*!
 * @file        board_apm32f072_eval.h
 *
 * @brief       This file contains definitions for APM32F072 EVAL board's Leds, push-buttons hardware resources
 *
 * @version     V1.0.0
 *
 * @date        2022-09-29
 *
 * @attention
 *
 *  Copyright (C) 2022 Geehy Semiconductor
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

/* Define to prevent recursive inclusion */
#ifndef __BOARD_APM32F072_EVAL_H
#define __BOARD_APM32F072_EVAL_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "main.h"
#include "apm32f0xx_usart.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup Board
  @{
*/

/** @addtogroup Board_APM32F072_EVAL
  @{
*/

/** @defgroup APM32F072_EVAL_Enumerates Enumerates
  @{
  */

/**
 * @brief   LED type
 */
typedef enum
{
    LED1,
    LED2,
    LED3,
    LED4,
} Led_TypeDef;

/**
 * @brief   Button type
 */
typedef enum
{
    BUTTON_KEY1 = 0,
    BUTTON_KEY2 = 1,
    BUTTON_KEY3 = 2,
    BUTTON_KEY4 = 3,
} Button_TypeDef;

/**
 * @brief   Button mode type
 */
typedef enum
{
    BUTTON_MODE_GPIO = 0,
    BUTTON_MODE_EINT = 1
} ButtonMode_TypeDef;

/**
 * @brief   USART COM type
 */
typedef enum
{
    COM1 = 0,
    COM2 = 1
} COM_TypeDef;

/**@} end of group APM32F072_EVAL_Enumerates*/

/** @defgroup APM32F072_EVAL_Macros Macros
  @{
*/

#define LEDn                             4

 /**
 * @brief LED4
 */
#define LED4_PIN                         GPIO_PIN_10
#define LED4_GPIO_PORT                   GPIOF
#define LED4_GPIO_CLK                    RCM_AHB_PERIPH_GPIOF

/**
 * @brief LED3
 */
#define LED3_PIN                         GPIO_PIN_9
#define LED3_GPIO_PORT                   GPIOF
#define LED3_GPIO_CLK                    RCM_AHB_PERIPH_GPIOF
 /**
 * @brief LED2
 */
#define LED2_PIN                         GPIO_PIN_13
#define LED2_GPIO_PORT                   GPIOC
#define LED2_GPIO_CLK                    RCM_AHB_PERIPH_GPIOC

 /**
 * @brief LED1
 */
#define LED1_PIN                         GPIO_PIN_6
#define LED1_GPIO_PORT                   GPIOE
#define LED1_GPIO_CLK                    RCM_AHB_PERIPH_GPIOE


#define BUTTONn                          4

/**
 * @brief Key1 push-button
 */
#define KEY1_BUTTON_PIN                   GPIO_PIN_0
#define KEY1_BUTTON_GPIO_PORT             GPIOC
#define KEY1_BUTTON_GPIO_CLK              RCM_AHB_PERIPH_GPIOC

/**
 * @brief Key2 push-button
 */
#define KEY2_BUTTON_PIN                   GPIO_PIN_1
#define KEY2_BUTTON_GPIO_PORT             GPIOC
#define KEY2_BUTTON_GPIO_CLK              RCM_AHB_PERIPH_GPIOC

/**
 * @brief Key3 push-button
 */
#define KEY3_BUTTON_PIN                   GPIO_PIN_2
#define KEY3_BUTTON_GPIO_PORT             GPIOC
#define KEY3_BUTTON_GPIO_CLK              RCM_AHB_PERIPH_GPIOC

/**
 * @brief Key4 push-button
 */
#define KEY4_BUTTON_PIN                   GPIO_PIN_3
#define KEY4_BUTTON_GPIO_PORT             GPIOC
#define KEY4_BUTTON_GPIO_CLK              RCM_AHB_PERIPH_GPIOC

#define COMn                             2

/**
 * @brief Definition for COM port1, connected to USART1
 */
#define EVAL_COM1                        USART1
#define EVAL_COM1_CLK                    RCM_APB2_PERIPH_USART1

#define EVAL_COM1_TX_PIN                 GPIO_PIN_9
#define EVAL_COM1_TX_GPIO_PORT           GPIOA
#define EVAL_COM1_TX_GPIO_CLK            RCM_AHB_PERIPH_GPIOA
#define EVAL_COM1_TX_SOURCE              GPIO_PIN_SOURCE_9
#define EVAL_COM1_TX_AF                  GPIO_AF_PIN1

#define EVAL_COM1_RX_PIN                 GPIO_PIN_10
#define EVAL_COM1_RX_GPIO_PORT           GPIOA
#define EVAL_COM1_RX_GPIO_CLK            RCM_AHB_PERIPH_GPIOA
#define EVAL_COM1_RX_SOURCE              GPIO_PIN_SOURCE_10
#define EVAL_COM1_RX_AF                  GPIO_AF_PIN1

#define EVAL_COM1_IRQn                   USART1_IRQn
/**
 * @brief Definition for COM port2, connected to USART2
 */
#define EVAL_COM2                        USART2
#define EVAL_COM2_CLK                    RCM_APB1_PERIPH_USART2

#define EVAL_COM2_TX_PIN                 GPIO_PIN_2
#define EVAL_COM2_TX_GPIO_PORT           GPIOA
#define EVAL_COM2_TX_GPIO_CLK            RCM_AHB_PERIPH_GPIOA
#define EVAL_COM2_TX_SOURCE              GPIO_PIN_SOURCE_2
#define EVAL_COM2_TX_AF                  GPIO_AF_PIN1

#define EVAL_COM2_RX_PIN                 GPIO_PIN_3
#define EVAL_COM2_RX_GPIO_PORT           GPIOA
#define EVAL_COM2_RX_GPIO_CLK            RCM_AHB_PERIPH_GPIOA
#define EVAL_COM2_RX_SOURCE              GPIO_PIN_SOURCE_3
#define EVAL_COM2_RX_AF                  GPIO_AF_PIN1

#define EVAL_COM2_IRQn                   USART2_IRQn

/**@} end of group APM32F072_EVAL_Macros*/

/** @defgroup APM32F072_EVAL_Fuctions
  @{
  */

/* LED */
void APM_EVAL_LEDInit(Led_TypeDef Led);
void APM_EVAL_LEDOn(Led_TypeDef Led);
void APM_EVAL_LEDOff(Led_TypeDef Led);
void APM_EVAL_LEDToggle(Led_TypeDef Led);

/* Key button */
void APM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t APM_EVAL_PBGetState(Button_TypeDef Button);
void APM_EVAL_PB_Led_Isr(void);

/* COM */
void APM_EVAL_COMInit(COM_TypeDef COM);

#ifdef __cplusplus
}
#endif

#endif

/**@} end of group APM32F072_EVAL_Functions */
/**@} end of group Board_APM32F072_EVAL */
/**@} end of group Board */
