/*!
 * @file        usbd_descriptor.c
 *
 * @brief       usb device descriptor configuration
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
#include "usbd_descriptor.h"
#include "usbd_hid.h"
#include <stdio.h>
#include <string.h>

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

#define USBD_GEEHY_VID              12619
#define USBD_FS_PID                 1001
#define USBD_LANGID_STR             0x0409
#define USBD_MANUFACTURER_STR       "Geehy"
#define USBD_PRODUCT_STR            "APM32 HID"
#define USBD_CONFIGURATION_STR      "HID Config"
#define USBD_INTERFACE_STR          "HID Interface"

/**@} end of group USBD_HID_Macros*/

/** @defgroup USBD_HID_Functions Functions
  @{
  */

static USBD_DESC_INFO_T USBD_FS_DeviceDescHandler(uint8_t usbSpeed);
static USBD_DESC_INFO_T USBD_FS_ConfigDescHandler(uint8_t usbSpeed);
static USBD_DESC_INFO_T USBD_FS_InterfaceDescHandler(uint8_t usbSpeed);
static USBD_DESC_INFO_T USBD_FS_LangIdDescHandler(uint8_t usbSpeed);
static USBD_DESC_INFO_T USBD_FS_ManufacturerDescHandler(uint8_t usbSpeed);
static USBD_DESC_INFO_T USBD_FS_ProductDescHandler(uint8_t usbSpeed);
static USBD_DESC_INFO_T USBD_FS_SerialDescHandler(uint8_t usbSpeed);
#if USBD_SUP_LPM
static USBD_DESC_INFO_T USBD_FS_BosDescHandler(uint8_t usbSpeed);
#endif
static USBD_DESC_INFO_T USBD_OtherSpeedConfigDescHandler(uint8_t usbSpeed);
static USBD_DESC_INFO_T USBD_DevQualifierDescHandler(uint8_t usbSpeed);

/**@} end of group USBD_HID_Functions */

/** @defgroup USBD_HID_Structures Structures
  @{
  */

/* USB device descripotr handler */
USBD_DESC_T USBD_DESC_FS =
{
    "HID Mouse Descriptor",
    USBD_FS_DeviceDescHandler,
    USBD_FS_ConfigDescHandler,
    USBD_FS_InterfaceDescHandler,
    USBD_FS_LangIdDescHandler,
    USBD_FS_ManufacturerDescHandler,
    USBD_FS_ProductDescHandler,
    USBD_FS_SerialDescHandler,
#if USBD_SUP_LPM
    USBD_FS_BosDescHandler,
#endif
    NULL,
    USBD_OtherSpeedConfigDescHandler,
    USBD_DevQualifierDescHandler,
};

/**@} end of group USBD_HID_Structures*/

/** @defgroup USBD_HID_Variables Variables
  @{
  */

/**
 * @brief   Device descriptor
 */
uint8_t USBD_DeviceDesc[USBD_DEVICE_DESCRIPTOR_SIZE] =
{
    /* bLength */
    0x12,
    /* bDescriptorType */
    USBD_DESC_DEVICE,
    /* bcdUSB */
#if USBD_SUP_LPM
    0x01,            /*<! For resume test of USBCV3.0. Only support LPM USB device */
#else
    0x00,
#endif
    0x02,
    /* bDeviceClass */
    0x00,
    /* bDeviceSubClass */
    0x00,
    /* bDeviceProtocol */
    0x00,
    /* bMaxPacketSize */
    USBD_EP0_PACKET_MAX_SIZE,
    /* idVendor */
    USBD_GEEHY_VID & 0xFF, USBD_GEEHY_VID >> 8,
    /* idProduct */
    USBD_FS_PID & 0xFF, USBD_FS_PID >> 8,
    /* bcdDevice = 2.00 */
    0x00, 0x02,
    /* Index of string descriptor describing manufacturer */
    USBD_DESC_STR_MFC,
    /* Index of string descriptor describing product */
    USBD_DESC_STR_PRODUCT,
    /* Index of string descriptor describing the device serial number */
    USBD_DESC_STR_SERIAL,
    /* bNumConfigurations */
    USBD_SUP_CONFIGURATION_MAX_NUM,
};

/**
 * @brief   Configuration descriptor
 */
uint8_t USBD_ConfigDesc[USBD_CONFIG_DESCRIPTOR_SIZE] =
{
    /* bLength */
    0x09,
    /* bDescriptorType */
    USBD_DESC_CONFIGURATION,
    /* wTotalLength */
    USBD_CONFIG_DESCRIPTOR_SIZE & 0xFF,
    USBD_CONFIG_DESCRIPTOR_SIZE >> 8,

    /* bNumInterfaces */
    0x01,
    /* bConfigurationValue */
    0x01,
    /* iConfiguration */
    0x00,
    /* bmAttributes */
#if USBD_SUP_SELF_PWR
    0xE0,
#else
    0xA0,
#endif
    /* MaxPower */
    0x32,

    /* HID Mouse Interface */
    /* bLength */
    0x09,
    /* bDescriptorType */
    USBD_DESC_INTERFACE,
    /* bInterfaceNumber */
    0x00,
    /* bAlternateSetting */
    0x00,
    /* bNumEndpoints */
    0x02,
    /* bInterfaceClass */
    USBD_HID_ITF_CLASS_ID,
    /* bInterfaceSubClass */
    USBD_HID_SUB_CLASS_BOOT,
    /* bInterfaceProtocol */
    USBD_HID_ITF_PORTOCOL_KEYBOARD,
    /* iInterface */
    0x00,

    /* HID descriptor of Mouse */
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

    /* HID Mouse Endpoint */
    /* bLength */
    0x07,
    /* bDescriptorType: Endpoint */
    USBD_DESC_ENDPOINT,
    /* bEndpointAddress */
    USBD_HID_IN_EP_ADDR,
    /* bmAttributes */
    0x03,
    /* wMaxPacketSize: */
    USBD_HID_IN_EP_SIZE & 0xFF,
    USBD_HID_IN_EP_SIZE >> 8,
    /* bInterval: */
    USBD_HID_FS_INTERVAL,
		
		/* HID Mouse Endpoint */
    /* bLength */
    0x07,
    /* bDescriptorType: Endpoint */
    USBD_DESC_ENDPOINT,
    /* bEndpointAddress */
    USBD_HID_OUT_EP_ADDR,
    /* bmAttributes */
    0x03,
    /* wMaxPacketSize: */
    USBD_HID_IN_EP_SIZE & 0xFF,
    USBD_HID_IN_EP_SIZE >> 8,
    /* bInterval: */
    USBD_HID_FS_INTERVAL,
};

/**
 * @brief   Other speed configuration descriptor
 */
uint8_t USBD_OtherSpeedCfgDesc[USBD_CONFIG_DESCRIPTOR_SIZE] =
{
    /* bLength */
    0x09,
    /* bDescriptorType */
    USBD_DESC_OTHER_SPEED,
    /* wTotalLength */
    USBD_CONFIG_DESCRIPTOR_SIZE & 0xFF,
    USBD_CONFIG_DESCRIPTOR_SIZE >> 8,

    /* bNumInterfaces */
    0x01,
    /* bConfigurationValue */
    0x01,
    /* iConfiguration */
    0x00,
    /* bmAttributes */
#if USBD_SUP_SELF_PWR
    0xE0,
#else
    0xA0,
#endif
    /* MaxPower */
    0x32,

    /* HID Mouse Interface */
    /* bLength */
    0x09,
    /* bDescriptorType */
    USBD_DESC_INTERFACE,
    /* bInterfaceNumber */
    0x00,
    /* bAlternateSetting */
    0x00,
    /* bNumEndpoints */
    0x01,
    /* bInterfaceClass */
    USBD_HID_ITF_CLASS_ID,
    /* bInterfaceSubClass */
    USBD_HID_SUB_CLASS_BOOT,
    /* bInterfaceProtocol */
    USBD_HID_ITF_PORTOCOL_MOUSE,
    /* iInterface */
    0x00,

    /* HID descriptor of Mouse */
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

    /* HID Mouse Endpoint */
    /* bLength */
    0x07,
    /* bDescriptorType: Endpoint */
    USBD_DESC_ENDPOINT,
    /* bEndpointAddress */
    USBD_HID_IN_EP_ADDR,
    /* bmAttributes */
    0x03,
    /* wMaxPacketSize: */
    USBD_HID_IN_EP_SIZE & 0xFF,
    USBD_HID_IN_EP_SIZE >> 8,
    /* bInterval: */
    USBD_HID_FS_INTERVAL,
		
		/* HID Mouse Endpoint */
    /* bLength */
    0x07,
    /* bDescriptorType: Endpoint */
    USBD_DESC_ENDPOINT,
    /* bEndpointAddress */
    USBD_HID_OUT_EP_ADDR,
    /* bmAttributes */
    0x03,
    /* wMaxPacketSize: */
    USBD_HID_IN_EP_SIZE & 0xFF,
    USBD_HID_IN_EP_SIZE >> 8,
    /* bInterval: */
    USBD_HID_FS_INTERVAL,
};

#if USBD_SUP_LPM
/**
 * @brief   BOS descriptor
 */
uint8_t USBD_BosDesc[USBD_BOS_DESCRIPTOR_SIZE] =
{
    /* bLength */
    0x05,
    /* bDescriptorType */
    USBD_DESC_BOS,
    /* wtotalLength */
    0x0C, 0x00,
    /* bNumDeviceCaps */
    0x01,

    /* Device Capability */
    /* bLength */
    0x07,
    /* bDescriptorType */
    USBD_DEVICE_CAPABILITY_TYPE,
    /* bDevCapabilityType */
    USBD_20_EXTENSION_TYPE,
    /* bmAttributes */
    0x02, 0x02, 0x00, 0x00,
};
#endif

/**
 * @brief   Serial string descriptor
 */
uint8_t USBD_SerialStrDesc[USBD_SERIAL_STRING_SIZE] =
{
    USBD_SERIAL_STRING_SIZE,
    USBD_DESC_STRING,

    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '1', 0
};

/**
 * @brief   Language ID string descriptor
 */
uint8_t USBD_LandIDStrDesc[USBD_LANGID_STRING_SIZE] =
{
    /* Size */
    USBD_LANGID_STRING_SIZE,
    /* bDescriptorType */
    USBD_DESC_STRING,
    USBD_LANGID_STR & 0xFF, USBD_LANGID_STR >> 8
};

/**
 * @brief   Device qualifier descriptor
 */
uint8_t USBD_DevQualifierDesc[USBD_DEVICE_QUALIFIER_DESCRIPTOR_SIZE] =
{
    /* Size */
    USBD_DEVICE_QUALIFIER_DESCRIPTOR_SIZE,
    /* bDescriptorType */
    USBD_DESC_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    USBD_HID_FS_MP_SIZE, /* In FS device*/
    0x01,
    0x00,
};

/**@} end of group USBD_HID_Variables*/

/** @defgroup USBD_HID_Functions Functions
  @{
  */

/*!
 * @brief     USB device convert ascii string descriptor to unicode format
 *
 * @param     desc : descriptor string
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_DESC_Ascii2Unicode(uint8_t* desc)
{
    USBD_DESC_INFO_T descInfo;
    uint8_t* buffer;
    uint8_t str[USBD_SUP_STR_DESC_MAX_NUM];

    uint8_t* unicode = str;
    uint16_t length;
    uint8_t index = 0;

    if (desc == NULL)
    {
        descInfo.desc = NULL;
        descInfo.size = 0;
    }
    else
    {
        buffer = desc;
        length = (strlen((char*)buffer) * 2) + 2;
        /* Get unicode descriptor */
        unicode[index] = length;

        index++;
        unicode[index] = USBD_DESC_STRING;
        index++;

        while (*buffer != '\0')
        {
            unicode[index] = *buffer;
            buffer++;
            index++;

            unicode[index] = 0x00;
            index++;
        }
    }

    descInfo.desc = unicode;
    descInfo.size = length;

    return descInfo;
}

/*!
 * @brief     USB device FS device descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_FS_DeviceDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    descInfo.desc = USBD_DeviceDesc;
    descInfo.size = sizeof(USBD_DeviceDesc);

    return descInfo;
}

/*!
 * @brief     USB device FS configuration descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_FS_ConfigDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    descInfo.desc = USBD_ConfigDesc;
    descInfo.size = sizeof(USBD_ConfigDesc);

    return descInfo;
}

#if USBD_SUP_LPM
/*!
 * @brief     USB device FS BOS descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_FS_BosDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    descInfo.desc = USBD_BosDesc;
    descInfo.size = sizeof(USBD_BosDesc);

    return descInfo;
}
#endif

/*!
 * @brief     USB device FS interface descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_FS_InterfaceDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    descInfo = USBD_DESC_Ascii2Unicode((uint8_t*)USBD_INTERFACE_STR);

    return descInfo;
}

/*!
 * @brief     USB device FS LANG ID string descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_FS_LangIdDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    descInfo.desc = USBD_LandIDStrDesc;
    descInfo.size = sizeof(USBD_LandIDStrDesc);

    return descInfo;
}

/*!
 * @brief     USB device FS manufacturer string descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_FS_ManufacturerDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    descInfo = USBD_DESC_Ascii2Unicode((uint8_t*)USBD_MANUFACTURER_STR);

    return descInfo;
}

/*!
 * @brief     USB device FS product string descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_FS_ProductDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    descInfo = USBD_DESC_Ascii2Unicode((uint8_t*)USBD_PRODUCT_STR);

    return descInfo;
}

/*!
 * @brief     USB device FS serial string descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_FS_SerialDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    descInfo.desc = USBD_SerialStrDesc;
    descInfo.size = sizeof(USBD_SerialStrDesc);

    return descInfo;
}

/*!
 * @brief     USB device other speed configuration descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_OtherSpeedConfigDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    /* Use FS configuration */
    descInfo.desc = USBD_OtherSpeedCfgDesc;
    descInfo.size = sizeof(USBD_OtherSpeedCfgDesc);

    return descInfo;
}

/*!
 * @brief     USB device device qualifier descriptor
 *
 * @param     usbSpeed : usb speed
 *
 * @retval    usb descriptor information
 */
static USBD_DESC_INFO_T USBD_DevQualifierDescHandler(uint8_t usbSpeed)
{
    USBD_DESC_INFO_T descInfo;

    /* Use FS configuration */
    descInfo.desc = USBD_DevQualifierDesc;
    descInfo.size = sizeof(USBD_DevQualifierDesc);

    return descInfo;
}

/**@} end of group USBD_HID_Functions */
/**@} end of group USBD_HID */
/**@} end of group Examples */
