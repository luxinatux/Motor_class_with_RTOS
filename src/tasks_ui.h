/** @file tasks_ui.h
 *  This file contains tasks which interact with a user. As these tasks support
 *  a very simple demonstration of multitasking, they don't do very much.
 * 
 *  @author  JR Ridgely
 *  @date    2021-Oct-19 Original file
 */

#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif

void task_ui (void* p_params);
void task_returns (void* p_params);
