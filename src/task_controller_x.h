/** @file task_controller_x.h
 *    This file contains the header file for the task controller x 
 * 
 *  @author Lucas Martos-Repath & Garret Gilmore
 *  @date   15 Nov 2021 Original file
 *  @date   7 Dec 2021
 */


#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <shares.h>

#ifndef _TASK_CONTROLLER_X
#define _TASK_CONTROLLER_X

/** @brief   Print a number, saying that it's a number.
 *  @details This is not a particularly useful function, except that it
 *           helps to show how a function can print things under Arduino.
 *  @param   number The number which is to be printed
 */

void task_controller_x(void* gxdata);

#endif