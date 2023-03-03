/*!
 * @file        Board_APM32F407_EVAL.c
 *
 * @brief       This file provides firmware functions to manage Leds and key buttons
 *
 * @version     V1.0.0
 *
 * @date        2022-05-25
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
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

#include "Board_APM32F407_EVAL.h"

/** @defgroup APM32F407_EVAL_Private_Variables
  * @{
  */
GPIO_T* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK};

GPIO_T* BUTTON_PORT[BUTTONn] =
{
    KEY1_BUTTON_GPIO_PORT,
    KEY2_BUTTON_GPIO_PORT,
    KEY3_BUTTON_GPIO_PORT,
    KEY4_BUTTON_GPIO_PORT
};

const uint16_t BUTTON_PIN[BUTTONn] =
{
    KEY1_BUTTON_PIN,
    KEY2_BUTTON_PIN,
    KEY3_BUTTON_PIN,
    KEY4_BUTTON_PIN
};

const uint32_t BUTTON_CLK[BUTTONn] =
{
    KEY1_BUTTON_GPIO_CLK,
    KEY2_BUTTON_GPIO_CLK,
    KEY3_BUTTON_GPIO_CLK,
    KEY4_BUTTON_GPIO_CLK,
};

const EINT_LINE_T BUTTON_EINT_LINE[BUTTONn] =
{
    KEY1_BUTTON_EINT_LINE,
    KEY2_BUTTON_EINT_LINE,
    KEY3_BUTTON_EINT_LINE,
    KEY4_BUTTON_EINT_LINE
};

const SYSCFG_PORT_T BUTTON_PORT_SOURCE[BUTTONn] =
{
    KEY1_BUTTON_EINT_PORT_SOURCE,
    KEY2_BUTTON_EINT_PORT_SOURCE,
    KEY3_BUTTON_EINT_PORT_SOURCE,
    KEY4_BUTTON_EINT_PORT_SOURCE
};

const SYSCFG_PIN_T BUTTON_PIN_SOURCE[BUTTONn] =
{
    KEY1_BUTTON_EINT_PIN_SOURCE,
    KEY2_BUTTON_EINT_PIN_SOURCE,
    KEY3_BUTTON_EINT_PIN_SOURCE,
    KEY4_BUTTON_EINT_PIN_SOURCE
};

const IRQn_Type BUTTON_IRQn[BUTTONn] =
{
    KEY1_BUTTON_EINT_IRQn,
    KEY2_BUTTON_EINT_IRQn,
    KEY3_BUTTON_EINT_IRQn,
    KEY4_BUTTON_EINT_IRQn
};

USART_T* COM_USART[COMn] = {EVAL_COM1, EVAL_COM2, EVAL_COM3};

GPIO_T* COM_TX_PORT[COMn] = {EVAL_COM1_TX_GPIO_PORT, EVAL_COM2_TX_GPIO_PORT, EVAL_COM3_TX_GPIO_PORT};

GPIO_T* COM_RX_PORT[COMn] = {EVAL_COM1_RX_GPIO_PORT, EVAL_COM2_RX_GPIO_PORT, EVAL_COM3_RX_GPIO_PORT};

const GPIO_PIN_SOURCE_T COM_TX_PIN_SOURCE[COMn] = {EVAL_COM1_TX_PIN_SOURCE, EVAL_COM2_TX_PIN_SOURCE, EVAL_COM3_TX_PIN_SOURCE};

const GPIO_PIN_SOURCE_T COM_RX_PIN_SOURCE[COMn] = {EVAL_COM1_RX_PIN_SOURCE, EVAL_COM2_RX_PIN_SOURCE, EVAL_COM3_RX_PIN_SOURCE};

const GPIO_AF_T COM_GPIO_AF[COMn] = {EVAL_COM1_GPIO_AF, EVAL_COM2_GPIO_AF, EVAL_COM3_GPIO_AF};

const uint32_t COM_USART_CLK[COMn] = {EVAL_COM1_CLK, EVAL_COM2_CLK, EVAL_COM3_CLK};

const uint32_t COM_TX_PORT_CLK[COMn] = {EVAL_COM1_TX_GPIO_CLK, EVAL_COM2_TX_GPIO_CLK, EVAL_COM3_TX_GPIO_CLK};

const uint32_t COM_RX_PORT_CLK[COMn] = {EVAL_COM1_RX_GPIO_CLK, EVAL_COM2_RX_GPIO_CLK, EVAL_COM3_RX_GPIO_CLK};

const uint16_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN, EVAL_COM2_TX_PIN, EVAL_COM3_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN, EVAL_COM2_RX_PIN, EVAL_COM3_RX_PIN};

/**
  * @}
  */

/** @defgroup APM32F407_EVAL_Private_Functions
  * @{
  */

/*!
 * @brief       Configures LED GPIO.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED1
 *              @arg LED2
 *              @arg LED3
 *
 * @retval      None
 */
void APM_EVAL_LEDInit(Led_TypeDef Led)
{
    GPIO_Config_T  configStruct;

    /** Enable the GPIO_LED Clock */
    RCM_EnableAHB1PeriphClock(GPIO_CLK[Led]);

    /** Configure the GPIO_LED pin */
    GPIO_ConfigStructInit(&configStruct);
    configStruct.pin = GPIO_PIN[Led];
    configStruct.mode = GPIO_MODE_OUT;
    configStruct.speed = GPIO_SPEED_50MHz;

    GPIO_Config(GPIO_PORT[Led], &configStruct);
    GPIO_PORT[Led]->BSCL = GPIO_PIN[Led];
}

/*!
 * @brief       Turns selected LED On.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED1
 *              @arg LED2
 *              @arg LED3
 *
 * @retval      None
 */
void APM_EVAL_LEDOn(Led_TypeDef Led)
{
    GPIO_PORT[Led]->BSCH |= GPIO_PIN[Led];
}

/*!
 * @brief       Turns selected LED Off.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED1
 *              @arg LED2
 *              @arg LED3
 *
 * @retval      None
 */
void APM_EVAL_LEDOff(Led_TypeDef Led)
{
    GPIO_PORT[Led]->BSCL |= GPIO_PIN[Led];
}

/*!
 * @brief       Toggles the selected LED.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED1
 *              @arg LED2
 *              @arg LED3
 *
 * @retval      None
 */
void APM_EVAL_LEDToggle(Led_TypeDef Led)
{
    GPIO_PORT[Led]->ODATA ^= GPIO_PIN[Led];
}

/*!
 * @brief       Configures Button GPIO and EINT Line.
 *
 * @param       Button: Specifies the Button to be configured.
 *              This parameter can be one of following parameters:
 *              @arg BUTTON_KEY1: Key1 Push Button
 *              @arg BUTTON_KEY2: Key2 Push Button
 *              @arg BUTTON_KEY3: Key3 Push Button
 *              @arg BUTTON_KEY4: Key4 Push Button
 *
 * @param       Button_Mode: Specifies Button mode.
 *              This parameter can be one of following parameters:
 *              @arg BUTTON_MODE_GPIO: Button will be used as simple IO
 *              @arg BUTTON_MODE_EINT: Button will be connected to EINT line
 *                   with interrupt generation capability
 *
 * @retval      None
 */
void APM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
    GPIO_Config_T     GPIO_configStruct;
    EINT_Config_T     EINT_configStruct;

    /** Enable the BUTTON Clock */
    RCM_EnableAHB1PeriphClock(BUTTON_CLK[Button]);

    /** Configure Button pin as input floating */
    GPIO_ConfigStructInit(&GPIO_configStruct);
    GPIO_configStruct.mode = GPIO_MODE_IN;
    GPIO_configStruct.pin = BUTTON_PIN[Button];
    GPIO_configStruct.pupd  = GPIO_PUPD_UP;
    GPIO_Config(BUTTON_PORT[Button], &GPIO_configStruct);

    if (Button_Mode == BUTTON_MODE_EINT)
    {
        /** Enable the SYSCFG Clock */
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

        /** Reset the SYSCFG Periph */
        SYSCFG_Reset();

        /** Connect Button EINT Line to Button GPIO Pin */
        SYSCFG_ConfigEINTLine(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

        /** Configure Button EINT line */
        EINT_configStruct.line = BUTTON_EINT_LINE[Button];
        EINT_configStruct.mode = EINT_MODE_INTERRUPT;
        EINT_configStruct.trigger = EINT_TRIGGER_FALLING;
        EINT_configStruct.lineCmd = ENABLE;
        EINT_Config(&EINT_configStruct);

        /** Enable and set Button EINT Interrupt to the lowest priority */
        NVIC_EnableIRQRequest(BUTTON_IRQn[Button], 0x0f, 0x0f);
    }
}

/*!
 * @brief       Returns the selected Button state.
 *
 * @param       Button: Specifies the Button to be configured.
 *              This parameter can be one of following parameters:
 *              @arg BUTTON_KEY1: Key1 Push Button
 *              @arg BUTTON_KEY2: Key2 Push Button
 *              @arg BUTTON_KEY3: Key3 Push Button
 *              @arg BUTTON_KEY4: Key4 Push Button
 *
 * @retval      The Button GPIO pin value.
 */
uint32_t APM_EVAL_PBGetState(Button_TypeDef Button)
{
    return GPIO_ReadInputBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/*!
 * @brief       Configures COM port.
 *
 * @param       COM: Specifies the COM port to be configured.
 *              This parameter can be one of following parameters:
 *              @arg COM1
 *              @arg COM2
 *              @arg COM3
 *
 * @retval      None
 */
void APM_EVAL_COMInit(COM_TypeDef COM, USART_Config_T* configStruct)
{
    GPIO_Config_T GPIO_configStruct;
    GPIO_ConfigStructInit(&GPIO_configStruct);

    /** Enable GPIO clock */
    RCM_EnableAHB1PeriphClock(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM]);

    if (COM == COM1)
    {
        RCM_EnableAPB2PeriphClock(COM_USART_CLK[COM]);
    }
    else
    {
        RCM_EnableAPB1PeriphClock(COM_USART_CLK[COM]);
    }

    /** Connect PXx to USARTx_Tx */
    GPIO_ConfigPinAF(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_GPIO_AF[COM]);

    /** Connect PXx to USARTx_Rx */
    GPIO_ConfigPinAF(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_GPIO_AF[COM]);

    /** Configure USART Tx as alternate function push-pull */
    GPIO_configStruct.mode = GPIO_MODE_AF;
    GPIO_configStruct.pin = COM_TX_PIN[COM];
    GPIO_configStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(COM_TX_PORT[COM], &GPIO_configStruct);

    /** Configure USART Rx as input floating */
    GPIO_configStruct.mode = GPIO_MODE_AF;
    GPIO_configStruct.pin = COM_RX_PIN[COM];
    GPIO_Config(COM_RX_PORT[COM], &GPIO_configStruct);

    /** USART configuration */
    USART_Config(COM_USART[COM], configStruct);

    /** Enable USART */
    USART_Enable(COM_USART[COM]);
}

/*!
 * @brief       Configures Buzzer.
 *
 * @param       None
 *
 * @retval      None
 */
void APM_EVAL_BuzzerInit(void)
{
    GPIO_Config_T GPIO_configStruct;

    RCM_EnableAHB1PeriphClock(EVAL_BUZZER_GPIO_CLK);
    
    GPIO_configStruct.pin = EVAL_BUZZER_PIN;
    GPIO_configStruct.mode = GPIO_MODE_OUT;
    GPIO_configStruct.speed = GPIO_SPEED_50MHz;
    GPIO_configStruct.otype = GPIO_OTYPE_PP;
    GPIO_configStruct.pupd = GPIO_PUPD_DOWN;
    GPIO_Config(EVAL_BUZZER_GPIO_PORT, &GPIO_configStruct);
    
    GPIO_ResetBit(EVAL_BUZZER_GPIO_PORT, EVAL_BUZZER_PIN);
}

/*!
 * @brief       Turns Buzzer On.
 *
 * @param       None
 *
 * @retval      None
 */
void APM_EVAL_BuzzerOn(void)
{
    GPIO_SetBit(EVAL_BUZZER_GPIO_PORT, EVAL_BUZZER_PIN);
}

/*!
 * @brief       Turns Buzzer Off.
 *
 * @param       None
 *
 * @retval      None
 */
void APM_EVAL_BuzzerOff(void)
{
    GPIO_ResetBit(EVAL_BUZZER_GPIO_PORT, EVAL_BUZZER_PIN);
}

/*!
 * @brief       Toggles the Buzzer.
 *
 * @param       None
 *
 * @retval      None
 */
void APM_EVAL_BuzzerToggle(void)
{
    EVAL_BUZZER_GPIO_PORT->ODATA ^= EVAL_BUZZER_PIN;
}
