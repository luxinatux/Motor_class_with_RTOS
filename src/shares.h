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

#ifndef _SHARES_H_
#define _SHARES_H_

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <taskqueue.h>
#include <taskshare.h>

/** @brief   Print a number, saying that it's a number.
 *  @details This is not a particularly useful function, except that it
 *           helps to show how a function can print things under Arduino.
 *  @param   number The number which is to be printed
 */

//extern Share<float> fft_share_gx;
//extern Share<float> fft_share_gy;

extern Queue<float> imu_queue_gx;
extern Queue<float> imu_queue_gy;

//extern Queue<float> omega_queue_x;
//extern Queue<float> omega_queue_y;

extern Share<float> imu_share_raw_x; 
extern Share<float> imu_share_raw_y;

extern Share<float> controller_update_x; 
extern Share<float> controller_update_y;

#endif