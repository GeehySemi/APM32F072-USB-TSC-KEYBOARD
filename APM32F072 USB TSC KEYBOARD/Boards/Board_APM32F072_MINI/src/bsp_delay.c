/*!
 * @file        bsp_delay.c
 *
 * @brief       Delay board support package program body
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

/* Includes */
#include "bsp_delay.h"

/** @addtogroup Board
  @{
*/

/** @addtogroup Board_APM32F072_MINI
  @{
*/

/** @defgroup APM32F072_MINI_Variables Variables
  @{
*/

__IO uint32_t delayTick;

/**@} end of group APM32F072_MINI_Variables*/

/** @defgroup APM32F072_MINI_Functions
  @{
*/

/*!
 * @brief       Configures Delay.
 *
 * @param       None
 *
 * @retval      None
 */
void APM_DelayInit(void)
{
    if (SysTick_Config(SystemCoreClock / 1000 / SYSTICK_FRQ))
    {
        while (1);
    }

    NVIC_SetPriority(SysTick_IRQn, 0U);
}

/*!
 * @brief       Decrement tick
 *
 * @param       None
 *
 * @retval      None
 */
void APM_DelayTickDec(void)
{
    if (delayTick != 0x00)
    {
        delayTick--;
    }
}

/*!
 * @brief       Configures Delay ms.
 *
 * @param       nms: Specifies the delay to be configured.
 *              This parameter can be one of following parameters:
 *              @arg nms
 *
 * @retval      None
 */
void APM_DelayMs(__IO uint32_t nms)
{
    delayTick = nms;

    while (delayTick != 0);
}

/**@} end of group APM32F072_MINI_Functions */
/**@} end of group Board_APM32F072_MINI */
/**@} end of group Board */
