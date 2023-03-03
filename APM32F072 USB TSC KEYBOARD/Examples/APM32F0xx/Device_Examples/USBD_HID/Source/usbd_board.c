/*!
 * @file        usbd_board.c
 *
 * @brief       This file provides firmware functions to USB board
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
#include "board.h"
#include "bsp_delay.h"
#include "usbd_board.h"
#include "usbd_core.h"
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_fmc.h"
#include "apm32f0xx_rcm.h"
#include "apm32f0xx_crs.h"
#include "apm32f0xx_misc.h"
#include "apm32f0xx_usb_device.h"

/** @addtogroup Examples
  * @brief USBD HID examples
  @{
  */

/** @addtogroup USBD_HID
  @{
  */

/** @defgroup USBD_HID_Variables Variables
  @{
  */

USBD_HANDLE_T usbDeviceHandler;

/**@} end of group USBD_HID_Variables*/

/** @defgroup USBD_HID_Functions Functions
  @{
  */

/*!
 * @brief       Init USB device clock
 *
 * @param       None
 *
 * @retval      None
 */
void USBD_ClockInit(void)
{
    uint32_t i;

    RCM->CTRL1_B.HSEEN = BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL1_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL1_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 1 wait state */
        FMC->CTRL1_B.WS = 1;

        /* HCLK = SYSCLK */
        RCM->CFG1_B.AHBPSC = 0X00;

        /* PCLK = HCLK */
        RCM->CFG1_B.APB1PSC = 0X00;

        /* PLL: HSE * 6 */
        RCM->CFG1_B.PLLSRCSEL = 2;
        RCM->CFG1_B.PLLMULCFG = 4;

        /* Enable PLL */
        RCM->CTRL1_B.PLLEN = 1;

        /* Wait PLL Ready */
        while (RCM->CTRL1_B.PLLRDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG1_B.SCLKSEL = 2;

        /* Wait till PLL is used as system clock source */
        while (RCM->CFG1_B.SCLKSWSTS != 0x02);
    }
    
    RCM_EnableHSI48();
    RCM_ConfigUSBCLK(RCM_USBCLK_HSI48);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USB);
    
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CRS);
    CRS_ConfigSynchronizationSource(CRS_SYNC_SOURCE_USB);
    CRS_EnableAutomaticCalibration();
    CRS_EnableFrequencyErrorCounter();
}

/*!
 * @brief       Init USB hardware
 *
 * @param       usbInfo:
 *
 * @retval      None
 */
void USBD_HardwareInit(USBD_INFO_T* usbInfo)
{
    /* Configure USB clock */
    USBD_ClockInit();
    
    /* Set systick as USB delay clock source*/
    APM_DelayInit();

    /* Link structure */
    usbDeviceHandler.usbGlobal    = USBD;

    /* Link data */
    usbDeviceHandler.dataPoint    = usbInfo;
    usbInfo->dataPoint            = &usbDeviceHandler;

    usbDeviceHandler.usbCfg.sofStatus           = DISABLE;
    usbDeviceHandler.usbCfg.speed               = USB_SPEED_FSLS;
    usbDeviceHandler.usbCfg.devEndpointNum      = 8;
    usbDeviceHandler.usbCfg.lowPowerStatus      = DISABLE;
    usbDeviceHandler.usbCfg.lpmStatus           = DISABLE;
    usbDeviceHandler.usbCfg.batteryStatus       = DISABLE;

    /* NVIC */
    NVIC_EnableIRQRequest(USBD_IRQn, 1);

    /* Disable USB all global interrupt */
    USBD_DisableInterrupt(usbDeviceHandler.usbGlobal, 
                          USBD_INT_CTR | \
                          USBD_INT_WKUP | \
                          USBD_INT_SUS | \
                          USBD_INT_ERR | \
                          USBD_INT_RST | \
                          USBD_INT_SOF | \
                          USBD_INT_ESOF | \
                          USBD_INT_L1REQ);

    /* Init USB Core */
    USBD_Config(&usbDeviceHandler);

    USBD_ConfigPMA(&usbDeviceHandler, USBD_HID_EP_IN_ADDR, USBD_EP_BUFFER_SINGLE, USBD_HID_EP_IN_SIZE);

    USBD_StartCallback(usbInfo);
}

/*!
 * @brief       Reset USB hardware
 *
 * @param       usbInfo:usb handler information
 *
 * @retval      None
 */
void USBD_HardwareReset(USBD_INFO_T* usbInfo)
{
    RCM_DisableAPB1PeriphClock(RCM_APB1_PERIPH_USB);
    
    NVIC_DisableIRQRequest(USBD_IRQn);
}

/*!
 * @brief       USB device start event callback function
 *
 * @param       usbInfo
 *
 * @retval      None
 */
void USBD_StartCallback(USBD_INFO_T* usbInfo)
{
    USBD_Start(usbInfo->dataPoint);
}

/*!
 * @brief     USB device stop handler callback
 *
 * @param     usbInfo : usb handler information
 *
 * @retval    None
 */
void USBD_StopCallback(USBD_INFO_T* usbInfo)
{
    USBD_Stop(usbInfo->dataPoint);
}

/*!
 * @brief     USB device stop device mode handler callback
 *
 * @param     usbInfo : usb handler information
 *
 * @retval    None
 */
void USBD_StopDeviceCallback(USBD_INFO_T* usbInfo)
{
    USBD_StopDevice(usbInfo->dataPoint);
}

/*!
 * @brief     USB OTG device resume callback
 *
 * @param     usbdh: USB device handler
 *
 * @retval    None
 */
void USBD_ResumeCallback(USBD_HANDLE_T* usbdh)
{
    if (usbdh->usbCfg.lowPowerStatus == ENABLE)
    {
        /* Reset SLEEPDEEP bit and SLEEPONEXIT SCR */
        SCB->SCR &= ~((uint32_t)((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk)));
        USBD_ClockInit();
    }
    
    USBD_Resume(usbdh->dataPoint);
}

/*!
 * @brief     USB OTG device suspend callback
 *
 * @param     usbdh: USB device handler
 *
 * @retval    None
 */
void USBD_SuspendCallback(USBD_HANDLE_T* usbdh)
{
    USBD_Suspend(usbdh->dataPoint);

    if (usbdh->usbCfg.lowPowerStatus == ENABLE)
    {
        /* Set SLEEPDEEP bit and SLEEPONEXIT SCR */
        SCB->SCR |= (uint32_t)((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
    }
}

/*!
 * @brief     USB OTG device enum done callback
 *
 * @param     usbdh: USB device handler
 *
 * @retval    None
 */
void USBD_EnumDoneCallback(USBD_HANDLE_T* usbdh)
{
    USBD_DEVICE_SPEED_T speed = USBD_DEVICE_SPEED_FS;

    switch (usbdh->usbCfg.speed)
    {
        case USB_SPEED_FSLS:
            speed = USBD_DEVICE_SPEED_FS;
            break;

        default:
            /* Speed error status */
            break;
    }

    /* Set USB core speed */
    USBD_SetSpeed(usbdh->dataPoint, speed);

    /* Reset device */
    USBD_Reset(usbdh->dataPoint);
}

/*!
 * @brief     USB OTG device SETUP stage callback
 *
 * @param     usbdh: USB device handler
 *
 * @retval    None
 */
void USBD_SetupStageCallback(USBD_HANDLE_T* usbdh)
{
    USBD_SetupStage(usbdh->dataPoint, (uint8_t*)usbdh->setup);
}

/*!
 * @brief     USB OTG device data OUT stage callback
 *
 * @param     usbdh: USB device handler
 *
 * @param     epNum: endpoint number
 *
 * @retval    None
 */
void USBD_DataOutStageCallback(USBD_HANDLE_T* usbdh, uint8_t epNum)
{
    USBD_DataOutStage(usbdh->dataPoint, epNum, usbdh->epIN[epNum].buffer);
}

/*!
 * @brief     USB OTG device data IN stage callback
 *
 * @param     usbdh: USB device handler
 *
 * @param     epNum: endpoint number
 *
 * @retval    None
 */
void USBD_DataInStageCallback(USBD_HANDLE_T* usbdh, uint8_t epNum)
{
    USBD_DataInStage(usbdh->dataPoint, epNum, usbdh->epIN[epNum].buffer);
}

/*!
 * @brief     USB device set EP on stall status callback
 *
 * @param     usbInfo : usb handler information
 *
 * @param     epAddr: endpoint address
 *
 * @retval    None
 */
USBD_STA_T USBD_EP_StallCallback(USBD_INFO_T* usbInfo, uint8_t epAddr)
{
    USBD_STA_T usbStatus = USBD_OK;

    USBD_EP_Stall(usbInfo->dataPoint, epAddr);

    return usbStatus;
}

/*!
 * @brief     USB device clear EP stall status callback
 *
 * @param     usbInfo : usb handler information
 *
 * @param     epAddr: endpoint address
 *
 * @retval    None
 */
USBD_STA_T USBD_EP_ClearStallCallback(USBD_INFO_T* usbInfo, uint8_t epAddr)
{
    USBD_STA_T usbStatus = USBD_OK;

    USBD_EP_ClearStall(usbInfo->dataPoint, epAddr);

    return usbStatus;
}

/*!
 * @brief     USB device read EP stall status callback
 *
 * @param     usbInfo : usb handler information
 *
 * @param     epAddr: endpoint address
 *
 * @retval    Stall status
 */
uint8_t USBD_EP_ReadStallStatusCallback(USBD_INFO_T* usbInfo, uint8_t epAddr)
{
    return (USBD_EP_ReadStallStatus(usbInfo->dataPoint, epAddr));
}

/*!
 * @brief     USB device read EP last receive data size callback
 *
 * @param     usbInfo : usb handler information
 *
 * @param     epAddr: endpoint address
 *
 * @retval    size of last receive data
 */
uint32_t USBD_EP_ReadRxDataLenCallback(USBD_INFO_T* usbInfo, uint8_t epAddr)
{
    return USBD_EP_ReadRxDataLen(usbInfo->dataPoint, epAddr);
}

/*!
 * @brief     USB device open EP callback
 *
 * @param     usbInfo : usb handler information
 *
 * @param     epAddr: endpoint address
 *
 * @param     epType: endpoint type
 *
 * @param     epMps: endpoint maxinum of packet size
 *
 * @retval    None
 */
void USBD_EP_OpenCallback(USBD_INFO_T* usbInfo, uint8_t epAddr, \
                          USB_EP_TYPE_T epType, uint16_t epMps)
{
    USBD_EP_Open(usbInfo->dataPoint, epAddr, epType, epMps);
}

/*!
 * @brief     USB device close EP callback
 *
 * @param     usbInfo : usb handler information
 *
 * @param     epAddr: endpoint address
 *
 * @retval    None
 */
void USBD_EP_CloseCallback(USBD_INFO_T* usbInfo, uint8_t epAddr)
{
    USBD_EP_Close(usbInfo->dataPoint, epAddr);
}

/*!
 * @brief     USB device EP receive handler callback
 *
 * @param     usbInfo : usb handler information
 *
 * @param     epAddr : endpoint address
 *
 * @param     buffer : data buffer
 *
 * @param     length : length of data
 *
 * @retval    usb device status
 */
USBD_STA_T USBD_EP_ReceiveCallback(USBD_INFO_T* usbInfo, uint8_t epAddr, \
                                   uint8_t* buffer, uint32_t length)
{
    USBD_STA_T usbStatus = USBD_OK;

    USBD_EP_Receive(usbInfo->dataPoint, epAddr, buffer, length);

    return usbStatus;
}

/*!
 * @brief     USB device EP transfer handler callback
 *
 * @param     usbInfo : usb handler information
 *
 * @param     epAddr : endpoint address
 *
 * @param     buffer : data buffer
 *
 * @param     length : length of data
 *
 * @retval    usb device status
 */
USBD_STA_T USBD_EP_TransferCallback(USBD_INFO_T* usbInfo, uint8_t epAddr, \
                                    uint8_t* buffer, uint32_t length)
{
    USBD_STA_T usbStatus = USBD_OK;

    USBD_EP_Transfer(usbInfo->dataPoint, epAddr, buffer, length);

    return usbStatus;
}

/*!
 * @brief     USB device flush EP handler callback
 *
 * @param     usbInfo : usb handler information
 *
 * @param     epAddr : endpoint address
 *
 * @retval    usb device status
 */
USBD_STA_T USBD_EP_FlushCallback(USBD_INFO_T* usbInfo, uint8_t epAddr)
{
    USBD_STA_T usbStatus = USBD_OK;

    USBD_EP_Flush(usbInfo->dataPoint, epAddr);

    return usbStatus;
}

/*!
 * @brief     USB device set device address handler callback
 *
 * @param     usbInfo : usb handler information
 *
 * @param     address : address
 *
 * @retval    usb device status
 */
USBD_STA_T USBD_SetDevAddressCallback(USBD_INFO_T* usbInfo, uint8_t address)
{
    USBD_STA_T usbStatus = USBD_OK;

    USBD_SetDevAddress(usbInfo->dataPoint, address);

    return usbStatus;
}

/*!
 * @brief       USB OTG device SOF event callback function
 *
 * @param       usbhh: USB host handler.
 *
 * @retval      None
 */
void USBD_SOFCallback(USBD_HANDLE_T* usbdh)
{
    USBD_HandleSOF(usbdh->dataPoint);
}

/*!
 * @brief     USB OTG device ISO IN in complete callback
 *
 * @param     usbdh: USB device handler
 *
 * @param     epNum: endpoint number
 *
 * @retval    None
 */
void USBD_IsoInInCompleteCallback(USBD_HANDLE_T* usbdh, uint8_t epNum)
{
    USBD_IsoInInComplete(usbdh->dataPoint, epNum);
}

/*!
 * @brief     USB OTG device ISO OUT in complete callback
 *
 * @param     usbdh: USB device handler
 *
 * @param     epNum: endpoint number
 *
 * @retval    None
 */
void USBD_IsoOutInCompleteCallback(USBD_HANDLE_T* usbdh, uint8_t epNum)
{
    USBD_IsoOutInComplete(usbdh->dataPoint, epNum);
}

/*!
 * @brief     USB OTG device connect callback
 *
 * @param     usbdh: USB device handler
 *
 * @retval    None
 */
void USBD_ConnectCallback(USBD_HANDLE_T* usbdh)
{
    USBD_Connect(usbdh->dataPoint);
}

/*!
 * @brief     USB OTG device disconnect callback
 *
 * @param     usbdh: USB device handler
 *
 * @retval    None
 */
void USBD_DisconnectCallback(USBD_HANDLE_T* usbdh)
{
    USBD_Disconnect(usbdh->dataPoint);
}

/**@} end of group USBD_HID_Functions */
/**@} end of group USBD_HID */
/**@} end of group Examples */
