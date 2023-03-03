/*!
 * @file        Board.c
 *
 * @brief       This file provides firmware functions to manage Leds and push-buttons
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

#if defined (APM32F407_MINI)
    #include "Board_APM32F407_MINI/Src/Board_APM32F407_MINI.c"

#elif defined (APM32F407_EVAL)
    #include "Board_APM32F407_EVAL/Src/Board_APM32F407_EVAL.c"

#elif defined (APM32F407_ELE_HUETB)
    #include "Board_APM32F407_ELE_HUETB.c"

#elif defined (APM32F103_MINI)
#include "Board_APM32F103_MINI\src\Board_APM32F103_MINI.c"

#elif defined (APM32F103VCS_MINI)
#include "Board_APM32F103VCS_MINI\src\Board_APM32F103VCS_MINI.c"

#elif defined (APM32F107_MINI)
#include "Board_APM32F107_MINI\src\Board_APM32F107_MINI.c"

#elif defined (APM32F072_MINI)
#include "Board_APM32F072_MINI\src\Board_APM32F072_MINI.c"

#elif defined (APM32L072_MINI)
#include "Board_APM32L072_MINI\src\Board_APM32L072_MINI.c"

#elif defined BOARD_APM32F072_EVAL
#include "board_apm32f072_eval.h"

#else
    #error "Please select first the APM32 board to be used (in board.c)"
#endif

/** @addtogroup Board
  @{

*/

/**@} end of group Board */
