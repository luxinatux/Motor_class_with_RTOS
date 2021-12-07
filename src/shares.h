#ifndef _SHARES_H_
#define _SHARES_H_

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <taskqueue.h>
#include <taskshare.h>

//extern Share<float> fft_share_gx;
//extern Share<float> fft_share_gy;

extern Queue<float> imu_queue_gx;
extern Queue<float> imu_queue_gy;

//extern Queue<float> omega_queue_x;
//extern Queue<float> omega_queue_y;

extern Share<float> imu_share_raw_x; 
extern Share<float> imu_share_raw_y;

#endif