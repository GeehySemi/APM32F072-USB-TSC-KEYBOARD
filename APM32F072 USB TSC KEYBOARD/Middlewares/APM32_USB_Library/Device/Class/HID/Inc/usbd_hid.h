/*!
 * @file        usbd_hid.h
 *
 * @brief       usb device hid class handler header file
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
#ifndef _USBD_HID_H_
#define _USBD_HID_H_

/* Includes */
#include "usbd_core.h"

/** @addtogroup APM32_USB_Library
  @{
  */

/** @addtogroup USBD_HID_Class
  @{
  */

/** @defgroup USBD_HID_Macros Macros
  @{
*/

#define USBD_HID_MOUSE_REPORT_DESC_SIZE         63
#define USBD_HID_DESC_SIZE                      9
#define USBD_HID_FS_INTERVAL                    10
#define USBD_HID_HS_INTERVAL                    7
#define USBD_HID_IN_EP_ADDR                     0x81
#define USBD_HID_OUT_EP_ADDR                    0x01
#define USBD_HID_IN_EP_SIZE                     0x08
#define USBD_HID_FS_MP_SIZE                     0x40

#define USBD_CLASS_SET_IDLE                     0x0A
#define USBD_CLASS_GET_IDLE                     0x02

#define USBD_CLASS_SET_REPORT                   0x09
#define USBD_CLASS_GET_REPORT                   0x01

#define USBD_CLASS_SET_PROTOCOL                 0x0B
#define USBD_CLASS_GET_PROTOCOL                 0x03

/**@} end of group USBD_HID_Macros*/

/** @defgroup USBD_HID_Enumerates Enumerates
  @{
  */

/**
 * @brief    HID state type
 */
typedef enum
{
    USBD_HID_IDLE,
    USBD_HID_BUSY,
} USBD_HID_STATE_T;

/**@} end of group USBD_HID_Enumerates*/

/** @defgroup USBD_HID_Structures Structures
  @{
  */

/**
 * @brief    HID information management
 */
typedef struct
{
    uint8_t             state;
    uint8_t             epInAddr;
    uint8_t             altSettingStatus;
    uint8_t             idleStatus;
    uint8_t             protocol;
} USBD_HID_INFO_T;

extern USBD_CLASS_T USBD_HID_CLASS;

/**@} end of group USBD_HID_Structures*/

/** @defgroup USBD_HID_Functions Functions
  @{
  */

uint8_t USBD_HID_ReadInterval(USBD_INFO_T* usbInfo);
USBD_STA_T USBD_HID_TxReport(USBD_INFO_T* usbInfo, uint8_t* report, uint16_t length);

/**@} end of group USBD_HID_Functions */
/**@} end of group USBD_HID_Class */
/**@} end of group APM32_USB_Library */

#endif
