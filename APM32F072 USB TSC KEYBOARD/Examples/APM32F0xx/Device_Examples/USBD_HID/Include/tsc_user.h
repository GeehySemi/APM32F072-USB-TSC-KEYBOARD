/*!
 * @file        tsc_user.h
 *
 * @brief       Touch-Sensing user configuration and api file.
 *
 * @version     V1.0.0
 *
 * @date        2022-09-29
 *
 * @attention
 *
 *  Copyright (C) 2022 Geehy Semiconductor
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

/* Define to prevent recursive inclusion */
#ifndef __TSC_USER_H
#define __TSC_USER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "tsc.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup TSC_KeyLinearRotate
  @{
  */

/** @defgroup TSC_KeyLinearRotate_Macros Macros
  @{
*/
#define CHANNEL_0_IO_MSK    (TSC_GROUP1_IO4)
#define CHANNEL_0_GRP_MSK   (TSC_GROUP1)
#define CHANNEL_0_SRC       (0) /*!< Index in source register (TSC->IOGXCR[]) */
#define CHANNEL_0_DEST      (0) /*!< Index in destination result array */

#define CHANNEL_1_IO_MSK    (TSC_GROUP1_IO2)
#define CHANNEL_1_GRP_MSK   (TSC_GROUP1)
#define CHANNEL_1_SRC       (0) /*!< Index in source register (TSC->IOGXCR[]) */
#define CHANNEL_1_DEST      (1) /*!< Index in destination result array */

#define CHANNEL_2_IO_MSK    (TSC_GROUP2_IO2)
#define CHANNEL_2_GRP_MSK   (TSC_GROUP2)
#define CHANNEL_2_SRC       (1) /*!< Index in source register (TSC->IOGXCR[]) */
#define CHANNEL_2_DEST      (2) /*!< Index in destination result array */

#define CHANNEL_3_IO_MSK    (TSC_GROUP2_IO3)
#define CHANNEL_3_GRP_MSK   (TSC_GROUP2)
#define CHANNEL_3_SRC       (1) /*!< Index in source register (TSC->IOGXCR[]) */
#define CHANNEL_3_DEST      (3) /*!< Index in destination result array */

#define CHANNEL_4_IO_MSK    (TSC_GROUP2_IO4)
#define CHANNEL_4_GRP_MSK   (TSC_GROUP2)
#define CHANNEL_4_SRC       (1) /*!< Index in source register (TSC->IOGXCR[]) */
#define CHANNEL_4_DEST      (4) /*!< Index in destination result array */

#define SHIELD_IO_MSK       (0)

#define BLOCK_0_NUMCHANNELS      (2)
#define BLOCK_0_MSK_CHANNELS     (CHANNEL_1_IO_MSK | CHANNEL_2_IO_MSK)
#define BLOCK_0_MSK_GROUPS       (CHANNEL_1_GRP_MSK | CHANNEL_2_GRP_MSK)
                                 
#define BLOCK_1_NUMCHANNELS      (2)
#define BLOCK_1_MSK_CHANNELS     (CHANNEL_0_IO_MSK | CHANNEL_4_IO_MSK)
#define BLOCK_1_MSK_GROUPS       (CHANNEL_0_GRP_MSK |CHANNEL_4_GRP_MSK)

#define BLOCK_2_NUMCHANNELS      (1)
#define BLOCK_2_MSK_CHANNELS     (CHANNEL_3_IO_MSK)
#define BLOCK_2_MSK_GROUPS       (CHANNEL_3_GRP_MSK)
/**@} end of group TSC_KeyLinearRotate_Macros*/

#define TOUCHKEY_PRESS(Num) ((MyTouchKeys[(Num)].p_Data->StateId == TSC_STATEID_DETECT))
#define TOUCHKEY_RELEASE(Num) ((MyTouchKeys[(Num)].p_Data->StateId == TSC_STATEID_RELEASE))

typedef enum
{
    TSC_TOUCH_K1 = 0x01,
    TSC_TOUCH_K2 = 0x02,
    TSC_TOUCH_K3 = 0x04,
    TSC_TOUCH_K4 = 0x08,
    TSC_TOUCH_K5 = 0x10,
} TSC_TOUCH_T;
enum
{
    HID_MOUSE_KEY_NULL,
    HID_MOUSE_KEY_LEFT,
    HID_MOUSE_KEY_RIGHT,
    HID_MOUSE_KEY_UP,
    HID_MOUSE_KEY_DOWN,
};
/* Timer tick */
extern uint8_t cnt50ms ;
extern uint8_t taskFlag ;
extern uint8_t tscPressStatus ;
extern uint16_t cntTick;
extern __IO uint32_t Global_EOA;
extern uint8_t keyRecord;
extern uint8_t tscPressRecord;
/** @defgroup TSC_KeyLinearRotate_Variables Variables
  @{
  */

extern CONST TSC_Block_T MyBlocks[];
extern CONST TSC_TouchKey_T MyTouchKeys[];
extern CONST TSC_Object_T MyObjects[];
extern TSC_ObjectGroup_T MyObjGroup;
extern uint32_t Global_ProcessSensor;

/**@} end of group TSC_KeyLinearRotate_Variables*/

/** @defgroup TSC_KeyLinearRotate_Functions Functions
  @{
  */
void Menu_TSCHandler(void);
void HidMouse_Proc(void);
uint8_t HidMouse_ReadKey(void);
void HidMouse_Write(uint8_t key);
void APM_EVAL_TMR14_Init(uint16_t period, uint16_t div);
void TMR14_Isr(void);
void MyKeys_ProcessOffState(void);
void MyKeys_ProcessErrorState(void);
void TSC_ReleaseHandler(void);
void TSC_DetectHandler(void);
void TSC_User_Config(void);
void TSC_User_Thresholds(void);
TSC_STATUS_T TSC_User_Action(void);


#ifdef __cplusplus
}
#endif

#endif /* __TSC_USER_H */

/**@} end of group TSC_KeyLinearRotate_Functions */
/**@} end of group TSC_KeyLinearRotate */
/**@} end of group Examples */
