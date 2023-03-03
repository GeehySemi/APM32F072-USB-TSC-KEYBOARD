/*!
 * @file        system_apm32l0xx.c
 *
 * @brief       CMSIS Cortex-M0+ Device Peripheral Access Layer System Source File
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

#include "apm32l0xx.h"

//#define SYSTEM_CLOCK_MSI       MSI_VALUE
//#define SYSTEM_CLOCK_HSE       HSE_VALUE
//#define SYSTEM_CLOCK_HSI16     HSI16_VALUE
#define SYSTEM_CLOCK_24MHz     (24000000)
//#define SYSTEM_CLOCK_32MHz     (32000000)

//#define VECT_TAB_SRAM
#define VECT_TAB_OFFSET          0x00

#ifdef SYSTEM_CLOCK_MSI
uint32_t SystemCoreClock         = SYSTEM_CLOCK_MSI;
#elif defined SYSTEM_CLOCK_HSE
uint32_t SystemCoreClock         = SYSTEM_CLOCK_HSE;
#elif defined SYSTEM_CLOCK_HSI16
uint32_t SystemCoreClock         = SYSTEM_CLOCK_HSI16;
#elif defined SYSTEM_CLOCK_24MHz
uint32_t SystemCoreClock         = SYSTEM_CLOCK_24MHz;
#elif defined SYSTEM_CLOCK_32MHz
uint32_t SystemCoreClock         = SYSTEM_CLOCK_32MHz;
#endif


const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};
const uint8_t PLLMulTable[9] = {3, 4, 6, 8, 12, 16, 24, 32, 48};

static void SystemClockConfig(void);

#ifdef SYSTEM_CLOCK_MSI
static void SystemClockMSI(void);
#elif defined SYSTEM_CLOCK_HSE
static void SystemClockHSE(void);
#elif defined SYSTEM_CLOCK_HSI16
static void SystemClockHSI(void);
#elif defined SYSTEM_CLOCK_24MHz
static void SystemClock24M(void);
#elif defined SYSTEM_CLOCK_32MHz
static void SystemClock32M(void);
#endif

/*!
 * @brief       Setup the microcontroller system
 *
 * @param       None
 *
 * @retval      None
 */
void SystemInit(void)
{
    /** Set MSIEN bit */
    RCM->CTRL_B.MSIEN = BIT_SET;
    /** Reset SCLKSEL, AHBPSC, APB1PSC, APB2PSC, MCOSEL and MCOPSC bits */
    RCM->CFG &= (uint32_t)0x80FFC00C;
    /** Reset HSE16EN, HSI16FEN, HSEEN, CSSEN and PLLEN bits */
    RCM->CTRL &= (uint32_t)0xFEF6FFFC;
    /** Reset HSEBCFG bit */
    RCM->CTRL_B.HSEBCFG = BIT_RESET;
    /** Reset PLLINSEL, PLLMUL, PLLOUTDIV bits */
    RCM->CFG &= (uint32_t)0xFF00FFFF;

    /** Disable all interrupts */
    RCM->INTEN = 0x00000000;

    SystemClockConfig();
#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET;
#else
    SCB->VTOR = FMC_BASE | VECT_TAB_OFFSET;
#endif
}

/*!
 * @brief       Update SystemCoreClock variable according to Clock Register Values
 *              The SystemCoreClock variable contains the core clock (HCLK)
 *
 * @param       None
 *
 * @retval      None
 */
void SystemCoreClockUpdate (void)
{
    uint32_t sysClock = 0, pllmul = 0, plldiv = 0, pllsource = 0, msirange = 0;

    /** Get SYSCLK source */
    sysClock = RCM->CFG_B.SCLKSWSTS;

    switch (sysClock)
    {
        /** sys clock is MSI */
        case 0:
        msirange = RCM->ICLKCAL_B.MSIR;
        SystemCoreClock = (32768 * (1 << (msirange + 1)));
        break;

        /** sys clock is HSI16 */
        case 1:
        SystemCoreClock = HSI16_VALUE;
        break;

        /** sys clock is HSE */
        case 2:
        SystemCoreClock = HSE_VALUE;
        break;

        /** sys clock is PLL */
        case 3:
        /** Get PLL clock source and multiplication factor */
        pllmul = RCM->CFG_B.PLLMUL;
        plldiv = RCM->CFG_B.PLLOUTDIV;
        pllsource = RCM->CFG_B.PLLINSEL;

        if (pllsource == 0)
        {
            /** HSI16 oscillator clock selected as PLL clock entry */
            SystemCoreClock = (((HSI16_VALUE) * pllmul) / plldiv);
        }
        else
        {
            /** HSE selected as PLL clock entry */
            SystemCoreClock = (((HSE_VALUE) * pllmul) / plldiv);
        }
        break;

        default: /** MSI used as system clock */
        msirange = RCM->ICLKCAL_B.MSIR;
        SystemCoreClock = (32768 * (1 << (msirange + 1)));
        break;
    }
    sysClock = AHBPrescTable[RCM->CFG_B.AHBPSC];
    SystemCoreClock >>= sysClock;
}

/*!
 * @brief       Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
static void SystemClockConfig(void)
{
    #ifdef SYSTEM_CLOCK_MSI
    SystemClockMSI();
    #elif defined SYSTEM_CLOCK_HSE
    SystemClockHSE();
    #elif defined SYSTEM_CLOCK_HSI16
    SystemClockHSI();
    #elif defined SYSTEM_CLOCK_24MHz
    SystemClock24M();
    #elif defined SYSTEM_CLOCK_32MHz
    SystemClock32M();
    #endif
}

#ifdef SYSTEM_CLOCK_MSI
/*!
 * @brief       Selects 2.1 MHz MSI as System clock source
 *
 * @param       None
 *
 * @retval      None
 */
static void SystemClockMSI(void)
{
    uint32_t i;

    RCM->CTRL_B.MSIEN = BIT_SET;

    for (i = 0; i < ((uint32_t)0x10000); i++)
    {
        if (RCM->CTRL_B.MSIRDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.MSIRDYFLG)
    {
        /** Select MSI as system clock source */
        RCM->CFG_B.SCLKSEL = 0x00;

        /** Wait till MSI is used as system clock source */
        while (RCM->CFG_B.SCLKSWSTS!= 0x00);
    }
}

#elif defined SYSTEM_CLOCK_HSE
/*!
 * @brief       Selects HSE as System clock source and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
static void SystemClockHSE(void)
{
    uint32_t i;

    RCM->CTRL_B.HSEEN= BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->ACCTRL_B.PREFEN = BIT_SET;
        /* Flash 0 wait state */
        FMC->ACCTRL_B.WAITP = 0;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;

        /* PCLK = HCLK */
        RCM->CFG_B.APB1PSC = 0X00;
        RCM->CFG_B.APB2PSC = 0x00;

        /* Select HSE as system clock source */
        RCM->CFG_B.SCLKSEL = 2;

        /** Wait till HSE is used as system clock source */
        while (RCM->CFG_B.SCLKSWSTS!= 0x02);
    }
}

#elif defined SYSTEM_CLOCK_HSI16
/*!
 * @brief       Sets System clock frequency to HSI and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SystemClockHSI(void)
{
    uint32_t i;

    RCM->CTRL_B.HSI16EN = BIT_SET;

    for (i = 0; i < HSI_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSI16RDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSI16RDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->ACCTRL_B.PREFEN = BIT_SET;
        /* Flash 1 wait state */
        FMC->ACCTRL_B.WAITP = 0;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;

        /* PCLK = HCLK */
        RCM->CFG_B.APB1PSC = 0X00;
        RCM->CFG_B.APB2PSC = 0X00;

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSEL = 1;

        /* Wait till PLL is used as system clock source */
        while (RCM->CFG_B.SCLKSWSTS!= 0x01);
    }
}

#elif defined SYSTEM_CLOCK_24MHz
/*!
 * @brief       Sets System clock frequency to 24MHz and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
static void SystemClock24M(void)
{
    uint32_t i;

    RCM->CTRL_B.HSEEN = BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->ACCTRL_B.PREFEN = BIT_SET;
        /* Flash 1 wait state */
        FMC->ACCTRL_B.WAITP = 1;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;

        /* PCLK = HCLK */
        RCM->CFG_B.APB1PSC = 0X00;
        RCM->CFG_B.APB2PSC = 0X00;
        
        /** PLL: (HSE * 6) / 2 */
        RCM->CFG_B.PLLINSEL  = 1;
        RCM->CFG_B.PLLOUTDIV = 1;
        RCM->CFG_B.PLLMUL    = 2;

        /** Enable PLL */
        RCM->CTRL_B.PLLEN = BIT_SET;

        /** Wait PLL Ready */
        while (RCM->CTRL_B.PLLRDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSEL = 3;

        /* Wait till PLL is used as system clock source */
        while (RCM->CFG_B.SCLKSWSTS!= 0x03);
    }
}

#elif defined SYSTEM_CLOCK_32MHz
/*!
 * @brief       Sets System clock frequency to 32MHz and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
static void SystemClock32M(void)
{
    uint32_t i;

    RCM->CTRL_B.HSEEN = BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->ACCTRL_B.PREFEN = BIT_SET;
        /* Flash 1 wait state */
        FMC->ACCTRL_B.WAITP = 1;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;

        /* PCLK = HCLK */
        RCM->CFG_B.APB1PSC = 0X00;
        RCM->CFG_B.APB2PSC = 0X00;
        
        /** PLL: (HSE * 6) / 2 */
        RCM->CFG_B.PLLINSEL  = 1;
        RCM->CFG_B.PLLOUTDIV = 1;
        RCM->CFG_B.PLLMUL    = 3;

        /** Enable PLL */
        RCM->CTRL_B.PLLEN = BIT_SET;

        /** Wait PLL Ready */
        while (RCM->CTRL_B.PLLRDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSEL = 3;

        /* Wait till PLL is used as system clock source */
        while (RCM->CFG_B.SCLKSWSTS!= 0x03);
    }
}
#endif

