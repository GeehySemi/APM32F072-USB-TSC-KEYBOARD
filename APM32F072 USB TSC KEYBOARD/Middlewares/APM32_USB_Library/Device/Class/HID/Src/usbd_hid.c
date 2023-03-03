/*!
 * @file        usbd_hid.c
 *
 * @brief       usb device hid class handler
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
#include "usbd_hid.h"
#include "usbd_stdReq.h"
#include "usbd_dataXfer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @addtogroup APM32_USB_Library
  @{
  */

/** @addtogroup USBD_HID_Class
  @{
  */

/** @defgroup USBD_HID_Functions Functions
  @{
  */

static USBD_STA_T USBD_HID_ClassInitHandler(USBD_INFO_T* usbInfo, uint8_t cfgIndex);
static USBD_STA_T USBD_HID_ClassDeInitHandler(USBD_INFO_T* usbInfo, uint8_t cfgIndex);
static USBD_STA_T USBD_HID_SOFHandler(USBD_INFO_T* usbInfo);
static USBD_STA_T USBD_HID_SetupHandler(USBD_INFO_T* usbInfo, USBD_REQ_SETUP_T* req);
static USBD_STA_T USBD_HID_DataInHandler(USBD_INFO_T* usbInfo, uint8_t epNum);

static USBD_DESC_INFO_T USBD_HID_ReportDescHandler(uint8_t usbSpeed);
static USBD_DESC_INFO_T USBD_HID_DescHandler(uint8_t usbSpeed);

/**@} end of group USBD_HID_Functions */

/** @defgroup USBD_HID_Structures Structures
  @{
  */

/* HID class handler */
USBD_CLASS_T USBD_HID_CLASS =
{
    /* Class handler */
    "Class HID",
    NULL,
    USBD_HID_ClassInitHandler,
    USBD_HID_ClassDeInitHandler,
    USBD_HID_SOFHandler,

    /* Control endpoint */
    USBD_HID_SetupHandler,
    NULL,
    NULL,
    /* Specific endpoint */
    USBD_HID_DataInHandler,
    NULL,
    NULL,
    NULL,
};

/**@} end of group USBD_HID_Structures*/

/** @defgroup USBD_HID_Variables Variables
  @{
  */

/**
 * @brief   HID descriptor
 */
uint8_t USBD_HIDDesc[USBD_HID_DESC_SIZE] =
{
    /* bLength */
    0x09,
    /* bDescriptorType: HID */
    USBD_DESC_HID,
    /* bcdHID */
    0x11, 0x01,
    /* bCountryCode */
    0x00,
    /* bNumDescriptors */
    0x01,
    /* bDescriptorType */
    USBD_DESC_HID_REPORT,
    /* wItemLength */
    USBD_HID_MOUSE_REPORT_DESC_SIZE & 0xFF, USBD_HID_MOUSE_REPORT_DESC_SIZE >> 8,
};

/**
 * @brief   HID mouse report descriptor
 */
uint8_t USBD_HIDReportDesc[USBD_HID_MOUSE_REPORT_DESC_SIZE] =
{
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    0x95, 0x05,                    //   REPORT_COUNT (5)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x05, 0x08,                    //   USAGE_PAGE (LEDs)
    0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x03,                    //   REPORT_SIZE (3)
    0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION
           /* End Collection                       */
};

/**@} end of group USBD_HID_Variables*/

/** @defgroup USBD_HID_Functions Functions
  @{
  */

/*!
 * @brief       USB device HID configuration handler
 *
 * @param       usbInfo: usb device information
 *
 * @param       cfgIndex: configuration index
 *
 * @retval      USB device operation status
 */
static USBD_STA_T USBD_HID_ClassInitHandler(USBD_INFO_T* usbInfo, uint8_t cfgIndex)
{
    USBD_STA_T usbStatus = USBD_OK;

    USBD_HID_INFO_T* usbDevHID;

    /* Link class data */
    usbInfo->devClass[usbInfo->classID]->classData = (USBD_HID_INFO_T*)malloc(sizeof(USBD_HID_INFO_T));
    usbDevHID = (USBD_HID_INFO_T*)usbInfo->devClass[usbInfo->classID]->classData;
    memset(usbDevHID, 0, sizeof(USBD_HID_INFO_T));

    USBD_USR_Debug("USBD_HID_INFO_T size %d\r\n", sizeof(USBD_HID_INFO_T));

    if (usbDevHID == NULL)
    {
        USBD_USR_LOG("usbDevHID is NULL");
        return USBD_FAIL;
    }

    usbDevHID->epInAddr = USBD_HID_IN_EP_ADDR;

    if (usbInfo->devSpeed == USBD_SPEED_FS)
    {
        usbInfo->devEpIn[usbDevHID->epInAddr & 0x0F].interval = USBD_HID_FS_INTERVAL;
    }
    else
    {
        usbInfo->devEpIn[usbDevHID->epInAddr & 0x0F].interval = USBD_HID_HS_INTERVAL;
    }

    /* Open endpoint */
    USBD_EP_OpenCallback(usbInfo, usbDevHID->epInAddr, EP_TYPE_INTERRUPT, USBD_HID_IN_EP_SIZE);
    usbInfo->devEpIn[usbDevHID->epInAddr & 0x0F].useStatus = ENABLE;

    usbDevHID->state = USBD_HID_IDLE;

    return usbStatus;
}

/*!
 * @brief       USB device HID reset handler
 *
 * @param       usbInfo: usb device information
 *
 * @param       cfgIndex: configuration index
 *
 * @retval      USB device operation status
 */
static USBD_STA_T USBD_HID_ClassDeInitHandler(USBD_INFO_T* usbInfo, uint8_t cfgIndex)
{
    USBD_STA_T usbStatus = USBD_OK;
    USBD_HID_INFO_T* usbDevHID = (USBD_HID_INFO_T*)usbInfo->devClass[usbInfo->classID]->classData;

    /* Close HID EP */
    USBD_EP_CloseCallback(usbInfo, usbDevHID->epInAddr);
    usbInfo->devEpIn[usbDevHID->epInAddr & 0x0F].interval = 0;
    usbInfo->devEpIn[usbDevHID->epInAddr & 0x0F].useStatus = DISABLE;

    if (usbInfo->devClass[usbInfo->classID]->classData != NULL)
    {
        free(usbInfo->devClass[usbInfo->classID]->classData);
        usbInfo->devClass[usbInfo->classID]->classData = 0;
    }

    return usbStatus;
}

/*!
 * @brief       USB device HID SOF handler
 *
 * @param       usbInfo: usb device information
 *
 * @retval      USB device operation status
 */
static USBD_STA_T USBD_HID_SOFHandler(USBD_INFO_T* usbInfo)
{
    USBD_STA_T  usbStatus = USBD_BUSY;

    return usbStatus;
}

/*!
 * @brief       USB device HID SETUP handler
 *
 * @param       usbInfo: usb device information
 *
 * @param       req: setup request
 *
 * @retval      USB device operation status
 */
static USBD_STA_T USBD_HID_SetupHandler(USBD_INFO_T* usbInfo, USBD_REQ_SETUP_T* req)
{
    USBD_STA_T  usbStatus = USBD_OK;
    USBD_HID_INFO_T* usbDevHID = (USBD_HID_INFO_T*)usbInfo->devClass[usbInfo->classID]->classData;

    USBD_DESC_INFO_T descInfo;
    uint8_t request;
    uint8_t reqType;
    uint16_t wValue = req->DATA_FIELD.wValue[0] | req->DATA_FIELD.wValue[1] << 8;
    uint16_t wLength = req->DATA_FIELD.wLength[0] | req->DATA_FIELD.wLength[1] << 8;
    uint16_t status = 0x0000;

    if (usbDevHID == NULL)
    {
        USBD_USR_LOG("usbDevHID is NULL");
        return USBD_FAIL;
    }

    request = req->DATA_FIELD.bRequest;
    reqType = usbInfo->reqSetup.DATA_FIELD.bmRequest.REQ_TYPE_B.type;

    switch (reqType)
    {
        case USBD_REQ_TYPE_STANDARD:
            switch (request)
            {
                /* HID descriptor */
                case USBD_STD_GET_DESCRIPTOR:
                    switch (req->DATA_FIELD.wValue[1])
                    {
                        case USBD_DESC_HID_REPORT:
                            descInfo = USBD_HID_ReportDescHandler(usbInfo->devSpeed);

                            descInfo.size = descInfo.size < wLength ? descInfo.size : wLength;
                            break;

                        case USBD_DESC_HID:
                            descInfo = USBD_HID_DescHandler(usbInfo->devSpeed);

                            descInfo.size = descInfo.size < wLength ? descInfo.size : wLength;
                            break;

                        default:
                            USBD_REQ_CtrlError(usbInfo, req);
                            usbStatus = USBD_FAIL;
                            break;
                    }

                    if (descInfo.desc != NULL)
                    {
                        USBD_CtrlSendData(usbInfo, descInfo.desc, descInfo.size);
                    }

                    break;

                case USBD_STD_GET_STATUS:
                    if (usbInfo->devState == USBD_DEV_CONFIGURE)
                    {
                        USBD_CtrlSendData(usbInfo, (uint8_t*)&status, 2);
                    }
                    else
                    {
                        USBD_REQ_CtrlError(usbInfo, req);
                        usbStatus = USBD_FAIL;
                    }
                    break;

                case USBD_STD_GET_INTERFACE:
                    if (usbInfo->devState == USBD_DEV_CONFIGURE)
                    {
                        USBD_CtrlSendData(usbInfo, (uint8_t*)&usbDevHID->altSettingStatus, 1);
                    }
                    else
                    {
                        USBD_REQ_CtrlError(usbInfo, req);
                        usbStatus = USBD_FAIL;
                    }
                    break;

                case USBD_STD_SET_INTERFACE:
                    if (usbInfo->devState == USBD_DEV_CONFIGURE)
                    {
                        usbDevHID->altSettingStatus = wValue;
                    }
                    else
                    {
                        USBD_REQ_CtrlError(usbInfo, req);
                        usbStatus = USBD_FAIL;
                    }
                    break;

                case USBD_STD_CLEAR_FEATURE:
                    break;

                default:
                    USBD_REQ_CtrlError(usbInfo, req);
                    usbStatus = USBD_FAIL;
                    break;
            }
            break;

        case USBD_REQ_TYPE_CLASS:
            switch (request)
            {
                case USBD_CLASS_SET_IDLE:
                    usbDevHID->idleStatus = req->DATA_FIELD.wValue[1];
                    break;

                case USBD_CLASS_GET_IDLE:
                    USBD_CtrlSendData(usbInfo, (uint8_t*)&usbDevHID->idleStatus, 1);
                    break;

                case USBD_CLASS_SET_PROTOCOL:
                    usbDevHID->protocol = req->DATA_FIELD.wValue[0];
                    break;

                case USBD_CLASS_GET_PROTOCOL:
                    USBD_CtrlSendData(usbInfo, (uint8_t*)&usbDevHID->protocol, 1);
                    break;

                default:
                    USBD_REQ_CtrlError(usbInfo, req);
                    usbStatus = USBD_FAIL;
                    break;
            }
            break;

        case USBD_REQ_TYPE_VENDOR:
            USBD_REQ_CtrlError(usbInfo, req);
            usbStatus = USBD_FAIL;
            break;

        default:
            usbStatus = USBD_FAIL;
            USBD_REQ_CtrlError(usbInfo, req);
            break;
    }

    return usbStatus;
}

/*!
 * @brief       USB device HID IN data handler
 *
 * @param       usbInfo: usb device information
 *
 * @param       epNum: endpoint number
 *
 * @retval      USB device operation status
 */
static USBD_STA_T USBD_HID_DataInHandler(USBD_INFO_T* usbInfo, uint8_t epNum)
{
    USBD_STA_T  usbStatus = USBD_OK;
    USBD_HID_INFO_T* usbDevHID = (USBD_HID_INFO_T*)usbInfo->devClass[usbInfo->classID]->classData;

    if (usbDevHID == NULL)
    {
        return USBD_FAIL;
    }
    
    usbDevHID->state = USBD_HID_IDLE;

    return usbStatus;
}

/*!
 * @brief     USB device HID report descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_HID_ReportDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    descInfo.desc = USBD_HIDReportDesc;
    descInfo.size = sizeof(USBD_HIDReportDesc);

    return descInfo;
}

/*!
 * @brief     USB device HID descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_HID_DescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    descInfo.desc = USBD_HIDDesc;
    descInfo.size = sizeof(USBD_HIDDesc);

    return descInfo;
}

/*!
 * @brief     USB device HID send report descriptor
 *
 * @param     usbInfo: usb device information
 *
 * @param     report: report buffer
 *
 * @param     length: report data length
 *
 * @retval    usb descriptor information
 */
USBD_STA_T USBD_HID_TxReport(USBD_INFO_T* usbInfo, uint8_t* report, uint16_t length)
{
    USBD_STA_T  usbStatus = USBD_OK;
    USBD_HID_INFO_T* usbDevHID = (USBD_HID_INFO_T*)usbInfo->devClass[usbInfo->classID]->classData;

    if (usbDevHID == NULL)
    {
        return USBD_FAIL;
    }

    switch (usbInfo->devState)
    {
        case USBD_DEV_CONFIGURE:
            if (usbDevHID->state == USBD_HID_IDLE)
            {
                usbDevHID->state = USBD_HID_BUSY;
                USBD_EP_TransferCallback(usbInfo, usbDevHID->epInAddr, report, length);
            }
            break;

        default:
            break;
    }

    return usbStatus;
}

/*!
 * @brief     USB device HID read interval
 *
 * @param     usbInfo: usb device information
 *
 * @retval    usb interval
 */
uint8_t USBD_HID_ReadInterval(USBD_INFO_T* usbInfo)
{
    uint8_t interval;

    if (usbInfo->devSpeed == USBD_SPEED_FS)
    {
        interval = USBD_HID_FS_INTERVAL;
    }
    else
    {
        interval = ((1 << (USBD_HID_HS_INTERVAL - 1)) / 8);
    }

    return interval;
}

/**@} end of group USBD_HID_Functions */
/**@} end of group USBD_HID_Class */
/**@} end of group APM32_USB_Library */