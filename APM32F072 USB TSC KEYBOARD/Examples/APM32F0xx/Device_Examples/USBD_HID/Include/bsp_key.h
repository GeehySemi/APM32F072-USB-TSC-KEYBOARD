/*!
 * @file        bsp_key.h
 *
 * @brief       Header for bsp_key.c module
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
#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "main.h"

/** @addtogroup Board
  @{
*/

/** @addtogroup Board_APM32F072_EVAL
  @{
*/

/** @defgroup APM32F072_EVAL_Macros Macros
  @{
*/
#define KEY1_PIN                GPIO_PIN_0
#define KEY2_PIN                GPIO_PIN_1
#define KEY3_PIN                GPIO_PIN_2
#define KEY4_PIN                GPIO_PIN_3
#define KEY_PORT                GPIOC

#define KEY1                    GPIO_ReadInputBit(KEY_PORT,KEY1_PIN)
#define KEY2                    GPIO_ReadInputBit(KEY_PORT,KEY2_PIN)
#define KEY3                    GPIO_ReadInputBit(KEY_PORT,KEY3_PIN)
#define KEY4                    GPIO_ReadInputBit(KEY_PORT,KEY4_PIN)

/**@} end of group APM32F072_EVAL_Macros*/

/** @defgroup APM32F072_EVAL_Enumerates Enumerates
  @{
  */

/**
 * @brief    Key value
 */
typedef enum
{
    KEY_ALL_REALEASED,          /*!< All key is realeased */
    KEY1_PRESSED,               /*!< KEY1 is pressed */
    KEY2_PRESSED,               /*!< KEY2 is pressed */
    KEY3_PRESSED,               /*!< KEY2 is pressed */
    KEY4_PRESSED,               /*!< KEY2 is pressed */
} KEY_VALUE_T;

/**
 * @brief    Key mode
 */
typedef enum
{
    KEY_MODE_SINGLE,                /*!< Single detect mode */
    KEY_MODE_CONTINUOUS,            /*!< Continuous detect mode */
} KEY_MODE_T;

/**@} end of group APM32F072_EVAL_Enumerates*/

/** @defgroup APM32F072_EVAL_Fuctions
  @{
  */
uint8_t Key_Scan(uint8_t mode);

#endif

/**@} end of group APM32F072_EVAL_Functions */
/**@} end of group Board_APM32F072_EVAL */
/**@} end of group Board */
