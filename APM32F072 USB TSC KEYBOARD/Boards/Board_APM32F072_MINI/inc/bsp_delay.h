/*!
 * @file        bsp_delay.h
 *
 * @brief       Header for bsp_delay.c module
 *
 * @version     V1.0.0
 *
 * @date        2023-01-16
 *
 * @attention
 *
 *  Copyright (C) 2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

/* Includes */
#include "apm32f0xx.h"
#include "apm32f0xx_misc.h"

/** @addtogroup Board
  @{
*/

/** @addtogroup Board_APM32F072_MINI
  @{
*/

/** @defgroup APM32F072_MINI_Macros Macros
  @{
*/

/* 100KHz */
#define SYSTICK_FRQ         1U

/**@} end of group APM32F072_MINI_Macros*/

/** @defgroup APM32F072_MINI_Functions
  @{
*/
void APM_DelayInit(void);
void APM_DelayTickDec(void);

/* Delay*/
void APM_DelayMs(__IO uint32_t nms);

/**@} end of group APM32F072_MINI_Functions */
/**@} end of group Board_APM32F072_MINI */
/**@} end of group Board */

#endif
