/*!
 * @file        usbd_board.h
 *
 * @brief       Header file for USB Board
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
#ifndef _USBD_BOARD_H_
#define _USBD_BOARD_H_

/* Includes */
#include "apm32f0xx.h"
#include "apm32f0xx_usb.h"
#include "apm32f0xx_usb_device.h"

/** @addtogroup Examples
  * @brief USBD HID examples
  @{
  */

/** @addtogroup USBD_HID
  @{
  */

/** @defgroup USBD_HID_Macros Macros
  @{
*/

#define USBD_SUP_CLASS_MAX_NUM              1
#define USBD_SUP_INTERFACE_MAX_NUM          1
#define USBD_SUP_CONFIGURATION_MAX_NUM      1
#define USBD_SUP_STR_DESC_MAX_NUM           512

#define USBD_HID_EP_IN_ADDR                 0x81
#define USBD_HID_EP_IN_SIZE                 0x100

/* Only support LPM USB device */
#define USBD_SUP_LPM                        0
#define USBD_SUP_SELF_PWR                   1
#define USBD_DEBUG_LEVEL                    1U

#if (USBD_DEBUG_LEVEL > 0U)
#define USBD_USR_LOG(...)   do { \
                            printf(__VA_ARGS__); \
                            printf("\r\n"); \
} while(0)
#else
#define USBD_USR_LOG(...) do {} while (0)
#endif

#if (USBD_DEBUG_LEVEL > 1U)
#define USBD_USR_Debug(...)   do { \
                            printf("Debug:"); \
                            printf(__VA_ARGS__); \
                            printf("\r\n"); \
} while(0)
#else
#define USBD_USR_Debug(...) do {} while (0)
#endif

/**@} end of group USBD_HID_Macros*/

/** @defgroup USBD_HID_Functions Functions
  @{
  */

/**@} end of group USBD_HID_Functions */
/**@} end of group USBD_HID */
/**@} end of group Examples */

#endif
