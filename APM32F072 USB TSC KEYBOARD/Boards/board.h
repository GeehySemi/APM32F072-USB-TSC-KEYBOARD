/*!
 * @file        Board.h
 *
 * @brief       Header file for Board
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
#ifndef BOARD_H
#define BOARD_H

#if defined (APM32F407_MINI)
    #include "Board_APM32F407_MINI/Inc/board_apm32f407_mini.h"

#elif defined (APM32F407_EVAL)
    #include "Board_APM32F407_EVAL/Inc/Board_APM32F407_EVAL.h"

#elif defined (APM32F407_ELE_HUETB)
    #include "Board_APM32F407_ELE_HUETB.h"

#elif defined (APM32F103_MINI)
#include "Board_APM32F103_MINI\inc\Board_APM32F103_MINI.h"

#elif defined (APM32F103VCS_MINI)
#include "Board_APM32F103VCS_MINI\inc\Board_APM32F103VCS_MINI.h"

#elif defined (APM32F107_MINI)
#include "Board_APM32F107_MINI\inc\Board_APM32F107_MINI.h"

#elif defined (APM32F072_MINI)
#include "Board_APM32F072_MINI\inc\Board_APM32F072_MINI.h"

#elif defined (APM32L072_MINI)
#include "Board_APM32L072_MINI\inc\Board_APM32L072_MINI.h"
#elif BOARD_APM32F072_EVAL
#include "board_apm32f072_eval.h"
#else
    #error "Please select first the APM32  board to be used (in board.h)"
#endif

/** @addtogroup Board
  @{
*/

/**@} end of group Board */

#endif
