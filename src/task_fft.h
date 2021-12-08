/** @file main.cpp
 *    This is a header file for the task_fft function
 * 
 *  @author Lucas Martos-Repath & Garret Gilmore
 *  @date   15 Nov 2021 Original file
 *  @date   7 Dec 2021
 */

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <shares.h>

#ifndef _TASK_FFT_
#define _TASK_FFT_

void task_fft(void* newgxdata);

#endif