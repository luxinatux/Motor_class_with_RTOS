/** @file shares.h
 *    This file contains an implementation of the Shares.h. This allows us to 
 *    keep track of the shared variables and queues between tasks and are initialized 
 *    in the main.cpp
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


//extern Share<float> fft_share_gx; //FFT share
//extern Share<float> fft_share_gy; //FFT share

extern Queue<float> imu_queue_gx; 
extern Queue<float> imu_queue_gy; 

//extern Queue<float> omega_queue_x;
//extern Queue<float> omega_queue_y;

extern Share<float> imu_share_raw_x; // Share to store raw angular velocity data x
extern Share<float> imu_share_raw_y; // Share to store raw angular velocity data y

extern Queue<float> imu_queue_x; //Queue to store raw angular velocity data x
extern  Queue<float> imu_queue_y; //Queue to store raw angular velocity data y

extern Share<float> controller_update_x; //Share to store values of throttle to send to motor task x
extern Share<float> controller_update_y; //Share to store values of throttle to send to motor task y

//extern Share<uint8_t> controller_state; //controller 1 is regular controller, controller 2 is FFT controller

#endif