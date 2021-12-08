/** @file task_motor1.h
 *    This is a header file for the task_motor1 function.
 * 
 *  @author Lucas Martos-Repath & Garret Gilmore
 *  @date   15 Nov 2021 Original file
 *  @date   7 Dec 2021
 */

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <shares.h>

#ifndef _TASK_MOTOR1
#define _TASK_MOTOR1

void task_motor1(void* data);

#endif

