/** @file main.cpp
 *    This file contains a simple demonstration program for ME507 which uses
 *    FreeRTOS to do multitasking. One of the tasks makes a square wave which
 *    can be viewed and measured with a signal analyzer or oscilloscope, while
 *    other tasks just print fairly useless things to the serial port. 
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

void task_controller_x(void* gxdata);

#endif