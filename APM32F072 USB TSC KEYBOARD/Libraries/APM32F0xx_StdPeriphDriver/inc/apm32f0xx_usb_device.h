/*!
 * @file        apm32f0xx_usb_device.h
 *
 * @brief       USB device function handle
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
#ifndef __APM32F0XX_USB_DEVICE_H
#define __APM32F0XX_USB_DEVICE_H

/* Includes */
#include "apm32f0xx.h"
#include "apm32f0xx_usb.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup USB_Device_Driver USB Device Driver
  @{
*/

/** @defgroup USB_Device_Macros Macros
  @{
*/

#if defined (USB_DEVICE)

#define USBD_WAKEUP_EINT_LINE                   0x40000

#define USBD_EP0_OUT_ADDR                       0x00
#define USBD_EP0_OUT_SIZE                       0x18

#define USBD_EP0_IN_ADDR                        0x80
#define USBD_EP0_IN_SIZE                        0x58

/**@} end of group USB_Device_Macros*/

/** @defgroup USB_Device_Enumerations Enumerations
  @{
*/

/**
 * @brief USB device link power mode status
 */
typedef enum
{
    USBD_LPM_LV0_ON,
    USBD_LPM_LV1_SLEEP,
    USBD_LPM_LV2_SUS,
    USBD_LPM_LV3_OFF,
} USBD_LPM_STA_T;

/**
 * @brief USB device link power mode
 */
typedef enum
{
    USBD_LPM_LV0,
    USBD_LPM_LV1,
} USBD_LOW_POWER_MODE_T;

/**@} end of group USB_Device_Enumerations*/

/** @defgroup USB_Device_Structures Structures
  @{
*/

/**
 * @brief USB device handle
 */
typedef struct
{
    USBD_T*                     usbGlobal;
    USBD_CFG_T                  usbCfg;
    
    USBD_ENDPOINT_INFO_T        epIN[8];
    USBD_ENDPOINT_INFO_T        epOUT[8];
    
    uint32_t                    setup[12];
    __IO uint8_t                address;

    uint8_t                     lpmStatus;
    uint8_t                     batteryStatus;
    USBD_LPM_STA_T              lpMode;
    uint32_t                    beslVal;
    
    void*                       dataPoint;
} USBD_HANDLE_T;

/**@} end of group USB_Device_Structures*/

/** @defgroup USB_Device_Functions Functions
  @{
*/

void USBD_IsrHandler(USBD_HANDLE_T* usbdh);
void USBD_ConfigPMA(USBD_HANDLE_T* usbdh, uint16_t epAddr, uint16_t bufferStatus, uint32_t pmaAddr);

void USBD_Start(USBD_HANDLE_T* usbdh);
void USBD_Stop(USBD_HANDLE_T* usbdh);
void USBD_StopDevice(USBD_HANDLE_T* usbdh);
void USBD_Config(USBD_HANDLE_T* usbdh);
void USBD_SetDevAddress(USBD_HANDLE_T* usbdh, uint8_t address);
void USBD_EP_Open(USBD_HANDLE_T* usbdh, uint8_t epAddr, \
                  USB_EP_TYPE_T epType, uint16_t epMps);
void USBD_EP_Close(USBD_HANDLE_T* usbdh, uint8_t epAddr);
void USBD_EP_Stall(USBD_HANDLE_T* usbdh, uint8_t epAddr);
void USBD_EP_ClearStall(USBD_HANDLE_T* usbdh, uint8_t epAddr);
uint8_t USBD_EP_ReadStallStatus(USBD_HANDLE_T* usbdh, uint8_t epAddr);
uint32_t USBD_EP_ReadRxDataLen(USBD_HANDLE_T* usbdh, uint8_t epAddr);
void USBD_EP_Flush(USBD_HANDLE_T* usbdh, uint8_t epAddr);
void USBD_EP_Receive(USBD_HANDLE_T* usbdh, uint8_t epAddr, \
                     uint8_t* buffer, uint32_t length);

void USBD_EP_Transfer(USBD_HANDLE_T* usbdh, uint8_t epAddr, \
                      uint8_t* buffer, uint32_t length);

void USBD_DisconnectCallback(USBD_HANDLE_T* usbdh);
void USBD_ConnectCallback(USBD_HANDLE_T* usbdh);
void USBD_ResumeCallback(USBD_HANDLE_T* usbdh);
void USBD_SuspendCallback(USBD_HANDLE_T* usbdh);
void USBD_EnumDoneCallback(USBD_HANDLE_T* usbdh);
void USBD_SetupStageCallback(USBD_HANDLE_T* usbdh);
void USBD_DataInStageCallback(USBD_HANDLE_T* usbdh, uint8_t epNum);
void USBD_DataOutStageCallback(USBD_HANDLE_T* usbdh, uint8_t epNum);
void USBD_SOFCallback(USBD_HANDLE_T* usbdh);
void USBD_IsoInInCompleteCallback(USBD_HANDLE_T* usbdh, uint8_t epNum);
void USBD_IsoOutInCompleteCallback(USBD_HANDLE_T* usbdh, uint8_t epNum);

void USBD_LpmModeCallback(USBD_HANDLE_T* usbdh, USBD_LOW_POWER_MODE_T lpMode);

/**@} end of group USB_Device_Functions*/
/**@} end of group USB_Device_Driver*/
/**@} end of group APM32F0xx_StdPeriphDriver*/

#endif /* defined (USB_DEVICE) */

#endif
