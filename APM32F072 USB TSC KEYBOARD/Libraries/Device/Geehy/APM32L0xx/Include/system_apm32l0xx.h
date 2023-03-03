/*!
 * @file        system_apm32l0xx.h
 *
 * @brief       CMSIS Cortex-M0 Device Peripheral Access Layer System Header File
 *
 * @version     V1.0.0
 *
 * @date        2021-12-25
 *
 * @attention
 *
 *  Copyright (C) 2020-2023 Geehy Semiconductor
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

#ifndef __SYSTEM_APM32L0XX_H
#define __SYSTEM_APM32L0XX_H

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SystemCoreClock;

/** @addtogroup SYSTEM_Fuctions Fuctions
  @{
*/

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

/**@} end of group SYSTEM_Fuctions*/

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_APM32L0XX_H */
