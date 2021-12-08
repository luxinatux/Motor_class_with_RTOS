/** @file main.cpp
 *    This is a head file for the task_imu_data function
 * 
 *  @author Lucas Martos-Repath & Garret Gilmore
 *  @date   15 Nov 2021 Original file
 *  @date   7 Dec 2021
 */
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <shares.h>

#ifndef _TASK_IMU_DATA_X
#define _TASK_IMU_DATA_X

void task_imu_data(void* imu_data);

#endif