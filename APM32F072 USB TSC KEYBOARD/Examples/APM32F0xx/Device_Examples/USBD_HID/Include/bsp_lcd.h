/*!
 * @file        bsp_lcd.h
 *
 * @brief       Header for bsp_lcd.c module
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
#ifndef __BSP_LCD_H
#define __BSP_LCD_H

/* Includes */
#include "main.h"

/** @addtogroup Board
  @{
*/

/** @addtogroup Board_APM32F072_EVAL
  @{
*/

/** @defgroup APM32F072_EVAL_Macros Macros
  @{
*/

#define LCD_SPI_BUS                     SPI2
#define LCD_SPI_BUS_CLK                 RCM_APB1_PERIPH_SPI2
#define LCD_SPI_MOSI_PIN                GPIO_PIN_4
#define LCD_SPI_MISO_PIN                GPIO_PIN_3
#define LCD_SPI_SCK_PIN                 GPIO_PIN_1
#define LCD_SPI_CS_PIN                  GPIO_PIN_0
#define LCD_SPI_GPIO_CLK                RCM_AHB_PERIPH_GPIOD
#define LCD_SPI_GPIO_PORT               GPIOD

#define LCD_SPI_MOSI_SOURCE             GPIO_PIN_SOURCE_4
#define LCD_SPI_MISO_SOURCE             GPIO_PIN_SOURCE_3
#define LCD_SPI_SCK_SOURCE              GPIO_PIN_SOURCE_1
#define LCD_SPI_CS_SOURCE               GPIO_PIN_SOURCE_0
#define LCD_SPI_GPIO_AF                 GPIO_AF_PIN1

#define LCD_SPI_MOSI_CLR()              GPIO_ClearBit(LCD_SPI_GPIO_PORT, LCD_SPI_MOSI_PIN)
#define LCD_SPI_MOSI_SET()              GPIO_SetBit(LCD_SPI_GPIO_PORT, LCD_SPI_MOSI_PIN)

#define LCD_SPI_MISO_CLR()              GPIO_ClearBit(LCD_SPI_GPIO_PORT, LCD_SPI_MISO_PIN)
#define LCD_SPI_MISO_SET()              GPIO_SetBit(LCD_SPI_GPIO_PORT, LCD_SPI_MISO_PIN)

#define LCD_SPI_SCK_CLR()               GPIO_ClearBit(LCD_SPI_GPIO_PORT, LCD_SPI_SCK_PIN)
#define LCD_SPI_SCK_SET()               GPIO_SetBit(LCD_SPI_GPIO_PORT, LCD_SPI_SCK_PIN)

#define LCD_SPI_CS_CLR()                GPIO_ClearBit(LCD_SPI_GPIO_PORT, LCD_SPI_CS_PIN)
#define LCD_SPI_CS_SET()                GPIO_SetBit(LCD_SPI_GPIO_PORT, LCD_SPI_CS_PIN)

#define LCD_DC_GPIO_CLK                 RCM_AHB_PERIPH_GPIOD
#define LCD_BLK_GPIO_CLK                RCM_AHB_PERIPH_GPIOC
#define LCD_RES_GPIO_CLK                RCM_AHB_PERIPH_GPIOD
#define LCD_DC_PIN                      GPIO_PIN_3
#define LCD_DC_GPIO_PORT                GPIOD
#define LCD_BLK_PIN                     GPIO_PIN_12
#define LCD_BLK_GPIO_PORT               GPIOC
#define LCD_RES_PIN                     GPIO_PIN_2
#define LCD_RES_GPIO_PORT               GPIOD

#define LCD_DC_CLR()                    GPIO_ClearBit(LCD_DC_GPIO_PORT, LCD_DC_PIN)
#define LCD_DC_SET()                    GPIO_SetBit(LCD_DC_GPIO_PORT, LCD_DC_PIN)

#define LCD_RES_CLR()                   GPIO_ClearBit(LCD_RES_GPIO_PORT, LCD_RES_PIN)
#define LCD_RES_SET()                   GPIO_SetBit(LCD_RES_GPIO_PORT, LCD_RES_PIN)

#define LCD_BLK_CLR()                   GPIO_ClearBit(LCD_BLK_GPIO_PORT, LCD_BLK_PIN)
#define LCD_BLK_SET()                   GPIO_SetBit(LCD_BLK_GPIO_PORT, LCD_BLK_PIN)

/* LCD display direction*/
#define LCD_HORIZONTAL 3

#if LCD_HORIZONTAL == 0 || LCD_HORIZONTAL == 1
#define LCD_WIDTH                       240
#define LCD_HEIGHT                      320

#else
#define LCD_WIDTH                       320
#define LCD_HEIGHT                      240
#endif

#define RGB2RGB565(R, G, B)             ((((R) & 0xF8) << 8) | (((G) & 0xFC) << 3) | (((B) & 0xF8) >> 3))

#define LCD_FCOLOR                      RGB2RGB565(0,222,152)
#define LCD_BCOLOR                      RGB2RGB565(255,255,255)
#define LCD_TEXT_FC                     RGB2RGB565(0,222,152)
#define LCD_TEXT_SELECT_FC              RGB2RGB565(255,255,255)
#define LCD_TEXT_BC                     RGB2RGB565(255,255,255)
#define LCD_TEXT_SELECT_BC              RGB2RGB565(0,222,152)

#define LCD_LINE_TITLE                  10
#define LCD_LINE_0                      50
#define LCD_LINE_1                      80
#define LCD_LINE_2                      110
#define LCD_LINE_3                      140
#define LCD_LINE_4                      170
#define LCD_LINE_5                      200
#define LCD_LINE_BOTTOM                 210
#define LCD_LINE_S_0                    50
#define LCD_LINE_S_1                    70
#define LCD_LINE_S_2                    90
#define LCD_LINE_S_3                    110
#define LCD_LINE_S_4                    130
#define LCD_LINE_S_5                    150
#define LCD_LINE_S_6                    170
#define LCD_LINE_S_7                    190

/**@} end of group APM32F072_EVAL_Macros*/

/** @defgroup APM32F072_EVAL_Enumerates Enumerates
  @{
  */

/**
 * @brief   LCD menu events
 */
typedef enum
{
    MENU_KEY_PREV = 1,
    MENU_KEY_NEXT,
    MENU_KEY_ENTER,
    MENU_KEY_RETURN,
} MENU_KEY_T;

/**
 * @brief   LCD operation status
 */
typedef enum
{
    LCD_OK,
    LCD_ERROR,
} LCD_ERROR_T;

/**@} end of group APM32F072_EVAL_Enumerates*/

/** @defgroup APM32F072_EVAL_Structures Structures
  @{
  */

/**
 * @brief   LCD menu information
 */
typedef struct MenuInfo
{
    uint8_t curMenu;
    uint8_t enterIndex;
    uint8_t prevIndex;
    uint8_t nextIndex;
    uint8_t retIndex;
    void (*function)(uint8_t param);
    uint8_t stateMenu;
} MENU_INFO_T;

/**@} end of group APM32F072_EVAL_Structures*/

/** @defgroup APM32F072_EVAL_Fuctions
  @{
  */
void Menu_DisplayInit(void);
void APM_LCDInit(void);
void LCD_DisplayFloatNum(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void LCD_DisplayIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void LCD_Clear(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void LCD_DisplayString(uint16_t x,uint16_t y,const char *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_DrawCircle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);
void LCD_DrawCorss(uint16_t x, uint16_t y, uint16_t color);
#endif

/**@} end of group APM32F072_EVAL_Functions */
/**@} end of group Board_APM32F072_EVAL */
/**@} end of group Board */
