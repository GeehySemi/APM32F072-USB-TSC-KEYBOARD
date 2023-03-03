/*!
 * @file        Board_APM32L072_MINI.c
 *
 * @brief       This file provides firmware functions to manage Leds and key buttons
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
#include "Board_APM32L072_MINI.h"
#include "apm32l0xx_gpio.h"
#include "apm32l0xx_eint.h"
#include "apm32l0xx_misc.h"

#include "stdio.h"
GPIO_T* GPIO_PORT[LEDn] = {LED2_GPIO_PORT, LED3_GPIO_PORT};
const GPIO_PIN_T GPIO_PIN[LEDn] = {LED2_PIN, LED3_PIN};
const RCM_GPIO_CLOCK_T GPIO_CLK[LEDn] = {LED2_GPIO_CLK, LED3_GPIO_CLK};

GPIO_T* BUTTON_PORT[BUTTONn] = {KEY1_BUTTON_GPIO_PORT, KEY2_BUTTON_GPIO_PORT};
const GPIO_PIN_T BUTTON_PIN[BUTTONn] = {KEY1_BUTTON_PIN, KEY2_BUTTON_PIN};
const RCM_GPIO_CLOCK_T BUTTON_CLK[BUTTONn] = {KEY1_BUTTON_GPIO_CLK, KEY2_BUTTON_GPIO_CLK};
const SYSCFG_PORT_T BUTTON_PORT_SOURCE[BUTTONn] = {KEY1_BUTTON_SYSCFG_PORT, KEY2_BUTTON_SYSCFG_PORT};
const SYSCFG_PIN_T BUTTON_PIN_SOURCE[BUTTONn] = {KEY1_BUTTON_EINT_PIN_SOURCE, KEY2_BUTTON_EINT_PIN_SOURCE};
const EINT_LINE_T BUTTON_EINT_LINE[BUTTONn] = {KEY1_BUTTON_EINT_LINE, KEY2_BUTTON_EINT_LINE};

USART_T* COM_USART[COMn] = {MINI_COM1, MINI_COM2};
GPIO_T* COM_TX_PORT[COMn] = {MINI_COM1_TX_GPIO_PORT, MINI_COM2_TX_GPIO_PORT};
GPIO_T* COM_RX_PORT[COMn] = {MINI_COM1_RX_GPIO_PORT, MINI_COM2_RX_GPIO_PORT};
const uint32_t COM_USART_CLK[COMn] = {MINI_COM1_CLK, MINI_COM2_CLK};

const RCM_GPIO_CLOCK_T COM_TX_PORT_CLK[COMn] = {MINI_COM1_TX_GPIO_CLK, MINI_COM2_TX_GPIO_CLK};

const RCM_GPIO_CLOCK_T COM_RX_PORT_CLK[COMn] = {MINI_COM1_RX_GPIO_CLK, MINI_COM2_RX_GPIO_CLK};

const GPIO_PIN_T COM_TX_PIN[COMn] = {MINI_COM1_TX_PIN, MINI_COM2_TX_PIN};

const GPIO_PIN_T COM_RX_PIN[COMn] = {MINI_COM1_RX_PIN, MINI_COM2_RX_PIN};

const GPIO_PIN_SOURCE_T COM_TX_PIN_SOURCE[COMn] = {MINI_COM1_TX_SOURCE, MINI_COM2_TX_SOURCE};

const GPIO_PIN_SOURCE_T COM_RX_PIN_SOURCE[COMn] = {MINI_COM1_RX_SOURCE, MINI_COM2_RX_SOURCE};

const GPIO_AF_T COM_TX_AF[COMn] = {MINI_COM1_TX_AF, MINI_COM2_TX_AF};

const GPIO_AF_T COM_RX_AF[COMn] = {MINI_COM1_RX_AF, MINI_COM2_RX_AF};


/*!
 * @brief       Configures LED GPIO.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED2
 *              @arg LED3
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_LEDInit(Led_TypeDef Led)
{
    GPIO_Config_T  gpioConfig;

    /** Enable the GPIO_LED Clock */
    RCM_EnableGPIOClock(GPIO_CLK[Led]);

    /** Configure the GPIO_LED pin */
    gpioConfig.pin = GPIO_PIN[Led];
    gpioConfig.mode = GPIO_MODE_OUT;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.speed = GPIO_SPEED_VERY_HIGH;
    gpioConfig.pupd = GPIO_PUPD_NO;

    GPIO_Config(GPIO_PORT[Led], &gpioConfig);

    GPIO_PORT[Led]->BSC = GPIO_PIN[Led];
}

/*!
 * @brief       Turns selected LED On.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED2
 *              @arg LED3
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_LEDOn(Led_TypeDef Led)
{
    GPIO_PORT[Led]->BR = GPIO_PIN[Led];
}

/*!
 * @brief       Turns selected LED Off.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED2
 *              @arg LED3
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_LEDOff(Led_TypeDef Led)
{
    GPIO_PORT[Led]->BSC = GPIO_PIN[Led];
}

/*!
 * @brief       Toggles the selected LED.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED2
 *              @arg LED3
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_LEDToggle(Led_TypeDef Led)
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
 * @param       Button_Mode: Specifies Button mode.
 *              This parameter can be one of following parameters:
 *              @arg BUTTON_MODE_GPIO: Button will be used as simple IO
 *              @arg BUTTON_MODE_EINT: Button will be connected to EINT line
 *                   with interrupt generation capability
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
    GPIO_Config_T gpioConfig;
    EINT_Config_T eintConfig;
    /** Enable the BUTTON Clock */
    RCM_EnableGPIOClock(BUTTON_CLK[Button]);

    /** Configure Button pin as input floating */
    gpioConfig.mode = GPIO_MODE_IN;
    gpioConfig.pupd = GPIO_PUPD_PU;
    gpioConfig.pin = BUTTON_PIN[Button];
    GPIO_Config(BUTTON_PORT[Button], &gpioConfig);
    
    if (Button_Mode == BUTTON_MODE_EINT)
    {
        /** Enable the SYSCFG Clock */
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

        /** Reset the SYSCFG Periph */
        SYSCFG_Reset();

        /** Connect Button EINT Line to Button GPIO Pin */
        SYSCFG_EINTLine(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

        /** Configure Button EINT line */
        eintConfig.line = BUTTON_EINT_LINE[Button];
        eintConfig.mode = EINT_MODE_INTERRUPT;
        eintConfig.trigger = EINT_TRIGGER_FALLING;
        eintConfig.lineCmd = ENABLE;
        EINT_Config(&eintConfig);

        /** Enable and set Button EINT Interrupt to the lowest priority */
        NVIC_EnableIRQRequest(EINT0_1_IRQn, 0x0f);
    }

}

/*!
 * @brief       Returns the selected Button state.
 *
 * @param       Button: Specifies the Button to be configured.
 *              This parameter can be one of following parameters:
 *              @arg BUTTON_KEY1: Key1 Push Button
 *              @arg BUTTON_KEY2: Key2 Push Button
 *
 * @retval      The Button GPIO pin value.
 *
 * @note
 */
uint32_t APM_MINI_PBGetState(Button_TypeDef Button)
{
    return GPIO_ReadInputBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/*!
 * @brief       The interrupt will happen when the button is press ,
 *              and the Led will be on
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_PB_Led_Isr()
{
    if (EINT_ReadStatusFlag(EINT_LINE1)==SET)
    {
        APM_MINI_LEDToggle(LED2);
        EINT_ClearStatusFlag(EINT_LINE1);
    }

    if (EINT_ReadStatusFlag(EINT_LINE0)==SET)
    {
        APM_MINI_LEDToggle(LED3);
        EINT_ClearStatusFlag(EINT_LINE0);
    }
}

/*!
 * @brief       Configures COM port.
 *
 * @param       COM: Specifies the COM port to be configured.
 *              This parameter can be one of following parameters:
 *              @arg COM1
 *              @arg COM2
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_COMInit(COM_TypeDef COM, USART_Config_T* usartConfigStruct)
{
    GPIO_Config_T gpioConfig;

    /** Enable GPIO clock */
    RCM_EnableGPIOClock(COM_TX_PORT_CLK[COM]);
    RCM_EnableGPIOClock(COM_RX_PORT_CLK[COM]);

    /** Enable COM1 or COM2 clock */
    if (COM == COM1)
    {
        RCM_EnableAPB2PeriphClock((RCM_APB2_PERIPH_T)COM_USART_CLK[COM]);
    }
    else
    {
        RCM_EnableAPB1PeriphClock((RCM_APB1_PERIPH_T)COM_USART_CLK[COM]);
    }

    /** Connect PXx to USARTx_Tx */
    GPIO_ConfigPinAF(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);

    /** Connect PXx to USARTx_Rx */
    GPIO_ConfigPinAF(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);

    /** Configure USART Tx as alternate function push-pull */
    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.pin = COM_TX_PIN[COM];
    gpioConfig.speed = GPIO_SPEED_VERY_HIGH;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.pupd = GPIO_PUPD_PU;
    GPIO_Config(COM_TX_PORT[COM], &gpioConfig);

    /** Configure USART Rx as input floating */
    gpioConfig.pin = COM_RX_PIN[COM];
    GPIO_Config(COM_RX_PORT[COM], &gpioConfig);

    USART_Config(COM_USART[COM], usartConfigStruct);

    /** Enable USART_Interrupt_RXBNEIE */
    USART_EnableInterrupt(COM_USART[COM], USART_INT_RXBNEIE);

    if (COM_USART[COM] == USART1)
    {
        NVIC_EnableIRQRequest(USART1_IRQn, 2);
    }
    else if (COM_USART[COM] == USART2)
    {
        NVIC_EnableIRQRequest(USART2_IRQn, 3);
    }

    /** Enable USART */
    USART_Enable(COM_USART[COM]);
}

