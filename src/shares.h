#ifndef _SHARES_H_
#define _SHARES_H_

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <taskqueue.h>
#include <taskshare.h>

extern Share<float> imu_share_gx ("gx Data");
extern Share<float> imu_share_gy ("gy Data");

extern Share<float> fft_share_gx ("FFT gx Data");
extern Share<float> fft_share_gy ("FFT gy Data");

extern Queue<float> imu_queue_gx (256, "gx Data");
extern Queue<float> imu_queue_gy (256, "gy Data");

extern Queue<float> omega_queue_x (256, "Omega x");
extern Queue<float> omega_queue_y (256, "Omega x");

extern Share<float> imu_share_raw_x ("Raw x data"); 
extern Share<float> imu_share_raw_y ("Raw y data");

#endif