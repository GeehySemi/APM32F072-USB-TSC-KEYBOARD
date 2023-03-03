/*!
 * @file        main.c
 *
 * @brief       Main program body
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
#include "bsp_lcd.h"
#include "board.h"
#include "bsp_delay.h"
#include "apm32f0xx_misc.h"
#include "apm32f0xx_usart.h"
#include "usb_device_user.h"
#include "usbd_hid.h"
#include <stdio.h>
#include "tsc_user.h"
#include "board_apm32f072_eval.h"
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



#define DEBUG_USART    USART1

/**@} end of group USBD_HID_Macros*/

/** @defgroup USBD_HID_Enumerates Enumerates
  @{
  */

/**
 * @brief User application state
 */
typedef enum
{
    USER_APP_INIT,
    USER_APP_RUN,
} USER_APP_STATE_T;

/**@} end of group USBD_HID_Enumerates*/

/** @defgroup USBD_HID_Functions Functions
  @{
  */

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      int
 */
int main(void)
{
	  uint8_t buffer[8] ={0,0,0,0,0};
    APM_DelayInit();
    APM_EVAL_LEDInit(LED1);
    APM_EVAL_LEDInit(LED2);
    APM_EVAL_LEDInit(LED3);
    APM_EVAL_PBInit(BUTTON_KEY1,BUTTON_MODE_GPIO);
    APM_EVAL_PBInit(BUTTON_KEY2,BUTTON_MODE_GPIO);
    APM_EVAL_PBInit(BUTTON_KEY3,BUTTON_MODE_GPIO);
    APM_EVAL_PBInit(BUTTON_KEY4,BUTTON_MODE_GPIO);
    APM_EVAL_COMInit(COM1);
	
	  APM_LCDInit();
	  Menu_DisplayInit();
	  APM_EVAL_TMR14_Init(1000,48);
	  TSC_User_Config();
    /* Init USB device */
    USB_DeviceInit();

    printf("USB Device HID Application\r\n");

    while (1)
    {
        HidMouse_Proc();
			  if (TSC_User_Action() == TSC_STATUS_OK)
        {
            if(taskFlag)
            {
                TSC_DetectHandler();
            }
            else
            {
                TSC_ReleaseHandler();	   
            }
						if(tscPressStatus!=0)
						{
							Menu_TSCHandler();
						}
//						else
//						{
//							 if(tscPressRecord!=0)
//							 {
//									tscPressRecord =0;
//									buffer[0] = 0;
//									buffer[2] = 0;
//								  buffer[3] = 0;
//									USBD_HID_TxReport(&gUsbDeviceFS, (uint8_t*)buffer, 8);	
//								  APM_DelayMs(16);
//							 }
//						}
        }
    }		
}

/*!
 * @brief       User application
 *
 * @param       None
 *
 * @retval      None
 */
void USB_DevUserApplication(void)
{
    static uint8_t userAppState = USER_APP_INIT;
    static uint8_t interval = 0;
    static int8_t report[4] = { 0 };

    switch (userAppState)
    {
        case USER_APP_INIT:
            interval = USBD_HID_ReadInterval(&gUsbDeviceFS);

            report[0] = 0;
            report[1] = 0;
            report[2] = 0;
            report[3] = 0;
            userAppState = USER_APP_RUN;
            break;

        case USER_APP_RUN:
            //if (!APM_MINI_PBGetState(BUTTON_KEY1))
            {
//                APM_DelayMs(10);
//                if (!APM_MINI_PBGetState(BUTTON_KEY1))
//                {
//                    report[1] = -5;
//                    USBD_HID_TxReport(&gUsbDeviceFS, (uint8_t*)report, 4);
//                }
            }

//            if (!APM_MINI_PBGetState(BUTTON_KEY2))
//            {
//                APM_DelayMs(10);
//                if (!APM_MINI_PBGetState(BUTTON_KEY2))
//                {
//                    report[1] = 5;
//                    USBD_HID_TxReport(&gUsbDeviceFS, (uint8_t*)report, 4);
//                }
//            }

            APM_DelayMs(interval);
            break;
    }
}

/*!
 * @brief       Redirect C Library function printf to serial port.
 *              After Redirection, you can use printf function.
 *
 * @param       ch:  The characters that need to be send.
 *
 * @param       *f:  pointer to a FILE that can recording all information
 *              needed to control a stream
 *
 * @retval      The characters that need to be send.
 */
int fputc(int ch, FILE* f)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, (uint8_t)ch);

    /* wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}

/**@} end of group USBD_HID_Functions */
/**@} end of group USBD_HID */
/**@} end of group Examples */
